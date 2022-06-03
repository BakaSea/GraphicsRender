#include "Cylinder.h"

bool CylinderXZ::hit(const Ray3f& ray, float tMin, float tMax, HitRecord& record) const {
    bool flag = false;
    float t = (center.y() - ray.origin().y()) / ray.direction().y();
    if (tMin < t && t < tMax) {
        Vector3f p = ray.point(t);
        if ((p - center).length() < radius) {
            //Need confirm u, v.
            record.u = 0;
            record.v = 0;
            record.t = t;
            record.material = material;
            record.p = p;
            record.normal = Vector3f(0, -1, 0);
            tMax = t;
            flag = true;
        }
    }
    Vector3f top = center + Vector3f(0, height, 0);
    t = (top.y() - ray.origin().y()) / ray.direction().y();
    if (tMin < t && t < tMax) {
        Vector3f p = ray.point(t);
        if ((p - top).length() < radius) {
            //Need confirm u, v.
            record.u = 0;
            record.v = 0;
            record.t = t;
            record.material = material;
            record.p = p;
            record.normal = Vector3f(0, 1, 0);
            tMax = t;
            flag = true;
        }
    }
    float ax = ray.origin().x(), bx = ray.direction().x();
    float az = ray.origin().z(), bz = ray.direction().z();
    float x0 = center.x(), z0 = center.z();
    float a = bx * bx + bz * bz;
    float b = 2.0f * (az * bz + ax * bx - bx * x0 - bz * z0);
    float c = ax * ax + az * az + x0 * x0 + z0 * z0 - radius * radius - 2 * ax * x0 - 2 * az * z0;
    float delta = b * b - 4 * a * c;
    if (delta > 0) {
        float t = (-b - float(sqrt(delta))) / (2.0f * a);
        if (tMin < t && t < tMax) {
            Vector3f p = ray.point(t);
            if (center.y() < p.y() && p.y() < center.y() + height) {
                record.t = t;
                record.u = 0;
                record.v = 0;
                record.p = p;
                record.normal = (p - Vector3f(center.x(), p.y(), center.z())) / radius;
                record.material = material;
                tMax = t;
                flag = true;
            }
        }
        t = (-b + float(sqrt(delta))) / (2.0f * a);
        if (tMin < t && t < tMax) {
            Vector3f p = ray.point(t);
            if (center.y() < p.y() && p.y() < center.y() + height) {
                record.t = t;
                record.u = 0;
                record.v = 0;
                record.p = p;
                record.normal = (p - Vector3f(center.x(), p.y(), center.z())) / radius;
                record.material = material;
                flag = true;
            }
        }
    }
    return flag;
}

bool CylinderXZ::getBoundingBox(float t0, float t1, AABB& box) const {
    box = AABB(center - Vector3f(radius, 0, radius), center + Vector3f(radius, height, radius));
    return true;
}
