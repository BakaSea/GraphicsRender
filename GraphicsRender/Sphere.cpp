#include "Sphere.h"

bool Sphere::hit(const Ray3f& ray, float tMin, float tMax, HitRecord& record) const {
    Vector3f oc = ray.origin() - center;
    float a = dot(ray.direction(), ray.direction());
    float b = 2.0f * dot(oc, ray.direction());
    float c = dot(oc, oc) - radius * radius;
    float delta = b * b - 4 * a * c;
    if (delta > 0) {
        float t = (-b - sqrt(delta)) / (2.0f * a);
        if (tMin < t && t < tMax) {
            record.t = t;
            record.u = 0;
            record.v = 0;
            record.p = ray.point(t);
            record.normal = (record.p - center) / radius;
            record.material = material;
            return true;
        }
        t = (-b + sqrt(delta)) / (2.0f * a);
        if (tMin < t && t < tMax) {
            record.t = t;
            record.u = 0;
            record.v = 0;
            record.p = ray.point(t);
            record.normal = (record.p - center) / radius;
            record.material = material;
            return true;
        }
    }
    return false;
}

bool Sphere::getBoundingBox(float t0, float t1, AABB& box) const {
    box = AABB(center - Vector3f(radius, radius, radius), center + Vector3f(radius, radius, radius));
    return true;
}
