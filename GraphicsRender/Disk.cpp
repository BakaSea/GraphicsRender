#include "Disk.h"

bool DiskXZ::hit(const Ray3f& ray, float tMin, float tMax, HitRecord& record) const {
    float t = (center.y() - ray.origin().y()) / ray.direction().y();
    if (t < tMin || t > tMax) return false;
    Vector3f p = ray.point(t);
    if ((p - center).length() <= radius) {
        //Need confirm u, v.
        record.u = 0;
        record.v = 0;
        record.t = t;
        record.material = material;
        record.p = p;
        record.normal = Vector3f(0, 1, 0);
        return true;
    } else return false;
}

bool DiskXZ::getBoundingBox(float t0, float t1, AABB& box) const {
    box = AABB(center - Vector3f(radius, 0.0001f, radius), center + Vector3f(radius, 0.0001f, radius));
    return true;
}

float DiskXZ::pdfValue(const Ray3f& ray) const {
    HitRecord record;
    if (hit(ray, 0.001f, FLT_MAX, record)) {
        float area = PI * radius * radius;
        float disSquared = record.t * record.t;
        float cosine = fabs(dot(ray.direction(), record.normal));
        return disSquared / (cosine * area);
    } else return 0.0f;
}

Vector3f DiskXZ::random(const Vector3f& origin, Sampler& sampler) const {
    Vector2f xy = sampler.generate2D([](Vector2f point) -> Vector2f {
        float r = sqrt(point.x());
        float theta = 2.0f * PI * point.y();
        return Vector2f(r * cos(theta), r * sin(theta));
    });
    Vector3f p = center + Vector3f(xy.x(), 0, xy.y()) * radius;
    return p - origin;
}

float DiskXZ::pdfWeight() const {
    return PI * radius * radius;
}
