#include "FlipNormalObject.h"

bool FlipNormalObject::hit(const Ray3f& ray, float tMin, float tMax, HitRecord& record) const {
    if (object->hit(ray, tMin, tMax, record)) {
        record.normal = -record.normal;
        return true;
    } else return false;
}

bool FlipNormalObject::getBoundingBox(float t0, float t1, AABB& box) const {
    return object->getBoundingBox(t0, t1, box);
}
