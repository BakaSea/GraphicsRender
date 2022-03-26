#include "Rectangle.h"

bool RectangleXY::hit(const Ray3f& ray, float tMin, float tMax, HitRecord& record) const {
    float t = (z - ray.origin().z()) / ray.direction().z();
    if (t < tMin || t > tMax) return false;
    float x = ray.origin().x() + t * ray.direction().x();
    float y = ray.origin().y() + t * ray.direction().y();
    if (x < x0 || x > x1 || y < y0 || y > y1) return false;
    record.u = (x - x0) / (x1 - x0);
    record.v = (y - y0) / (y1 - y0);
    record.t = t;
    record.material = material;
    record.p = ray.point(t);
    record.normal = Vector3f(0, 0, 1);
    return true;
}

bool RectangleXY::getBoundingBox(float t0, float t1, AABB& box) const {
    box = AABB(Vector3f(x0, y0, z - 0.0001f), Vector3f(x1, y1, z + 0.0001f));
    return true;
}

bool RectangleXZ::hit(const Ray3f& ray, float tMin, float tMax, HitRecord& record) const {
    float t = (y - ray.origin().y()) / ray.direction().y();
    if (t < tMin || t > tMax) return false;
    float x = ray.origin().x() + t * ray.direction().x();
    float z = ray.origin().z() + t * ray.direction().z();
    if (x < x0 || x > x1 || z < z0 || z > z1) return false;
    record.u = (x - x0) / (x1 - x0);
    record.v = (z - z0) / (z1 - z0);
    record.t = t;
    record.material = material;
    record.p = ray.point(t);
    record.normal = Vector3f(0, 1, 0);
    return true;
}

bool RectangleXZ::getBoundingBox(float t0, float t1, AABB& box) const {
    box = AABB(Vector3f(x0, y - 0.0001f, z0), Vector3f(x1, y + 0.0001f, z1));
    return true;
}

bool RectangleYZ::hit(const Ray3f& ray, float tMin, float tMax, HitRecord& record) const {
    float t = (x - ray.origin().x()) / ray.direction().x();
    if (t < tMin || t > tMax) return false;
    float y = ray.origin().y() + t * ray.direction().y();
    float z = ray.origin().z() + t * ray.direction().z();
    if (y < y0 || y > y1 || z < z0 || z > z1) return false;
    record.u = (y - y0) / (y1 - y0);
    record.v = (z - z0) / (z1 - z0);
    record.t = t;
    record.material = material;
    record.p = ray.point(t);
    record.normal = Vector3f(1, 0, 0);
    return true;
}

bool RectangleYZ::getBoundingBox(float t0, float t1, AABB& box) const {
    box = AABB(Vector3f(x - 0.0001f, y0, z0), Vector3f(x + 0.0001f, y1, z1));
    return true;
}
