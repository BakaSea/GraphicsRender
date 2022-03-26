#pragma once
#include "Object.h"

class Triangle : public Object {
public:
	Triangle() : material(nullptr), useVn(false) {}
	Triangle(const Vector3f& v0, const Vector3f& v1, const Vector3f& v2, Material* material);
	Triangle(const Vector3f& v0, const Vector3f& v1, const Vector3f& v2, const Vector2f& vt0, const Vector2f& vt1, const Vector2f& vt2, Material* material);
	void setVertexNormal(const Vector3f& vn0, const Vector3f& vn1, const Vector3f& vn2);
	bool hit(const Ray3f& ray, float tMin, float tMax, HitRecord& record) const override;
	bool getBoundingBox(float t0, float t1, AABB& box) const override;

private:
	Vector3f v0, v1, v2;
	Vector3f e0, e1;
	Vector3f normal;
	Vector2f vt0, vt1, vt2;
	Vector3f vn0, vn1, vn2;
	Material* material;
	bool useVn;
};
