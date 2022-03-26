#pragma once
#include "Object.h"

class CylinderXZ : public Object {
public:
	CylinderXZ() : radius(0), height(0), material(nullptr) {}
	CylinderXZ(const Vector3f& center, float radius, float height, Material* material) : center(center), radius(radius), height(height), material(material) {}
	bool hit(const Ray3f& ray, float tMin, float tMax, HitRecord& record) const override;
	bool getBoundingBox(float t0, float t1, AABB& box) const override;

private:
	Vector3f center;
	float radius;
	float height;
	Material* material;
};
