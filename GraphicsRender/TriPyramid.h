#pragma once
#include "Object.h"
#include "Triangle.h"

class TriPyramid : public Object {
public:
	TriPyramid() : material(nullptr) {}
	TriPyramid(const Vector3f& v0, const Vector3f& v1, const Vector3f& v2, const Vector3f& v3, Material* material);
	bool hit(const Ray3f& ray, float tMin, float tMax, HitRecord& record) const override;
	bool getBoundingBox(float t0, float t1, AABB& box) const override;

private:
	Triangle tri[4];
	Material* material;
};