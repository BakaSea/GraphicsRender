#pragma once
#include "Object.h"
#include "Material.h"

class Sphere : public Object {
public:
	Sphere() : radius(0.0f), material(nullptr) {}
	Sphere(Vector3f center, float radius, Material* material) : center(center), radius(radius), material(material) {}
	bool hit(const Ray3f& ray, float tMin, float tMax, HitRecord& record) const override;
	bool getBoundingBox(float t0, float t1, AABB& box) const override;

private:
	Vector3f center;
	float radius;
	Material* material;
};
