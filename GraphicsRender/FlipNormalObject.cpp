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

float FlipNormalObject::pdfValue(const Ray3f& ray) const {
    return object->pdfValue(ray);
}

Vector3f FlipNormalObject::random(const Vector3f& origin, Sampler& sampler) const {
    return object->random(origin, sampler);
}

float FlipNormalObject::pdfWeight() const {
    return object->pdfWeight();
}
