#pragma once
#include "Object.h"

class FlipNormalObject : public Object {
public:
	FlipNormalObject(Object* object) : object(object) {}
	~FlipNormalObject() {
		delete object;
	}
	bool hit(const Ray3f& ray, float tMin, float tMax, HitRecord& record) const override;
	bool getBoundingBox(float t0, float t1, AABB& box) const override;
	float pdfValue(const Ray3f& ray) const override;
	Vector3f random(const Vector3f& origin, Sampler& sampler) const override;
	float pdfWeight() const override;

private:
	Object* object;
};

