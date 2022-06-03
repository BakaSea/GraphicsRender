#pragma once
#include "Object.h"

class DiskXZ : public Object {
public:
	DiskXZ() : radius(0), material(nullptr) {}
	DiskXZ(const Vector3f& center, float radius, Material* material) : center(center), radius(radius), material(material) {}
	bool hit(const Ray3f& ray, float tMin, float tMax, HitRecord& record) const override;
	bool getBoundingBox(float t0, float t1, AABB& box) const override;
	float pdfValue(const Ray3f& ray) const override;
	Vector3f random(const Vector3f& origin, Sampler& sampler) const override;
	float pdfWeight() const override;

private:
	Vector3f center;
	float radius;
	Material* material;
};

