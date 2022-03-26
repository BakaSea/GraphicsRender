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

private:
	Object* object;
};

