#pragma once
#include <memory>
#include "Ray.h"
#include "AABB.h"
using namespace std;

class Material;

struct HitRecord {
	float t;
	float u;
	float v;
	Vector3f p;
	Vector3f normal;
	Material* material;
};

class Object {
public:
	virtual bool hit(const Ray3f& ray, float tMin, float tMax, HitRecord& record) const = 0;
	virtual bool getBoundingBox(float t0, float t1, AABB& box) const = 0;
	virtual float pdfValue(const Ray3f& ray) const {
		return 0;
	}
	virtual Vector3f random(const Vector3f& origin) const {
		return Vector3f(1, 0, 0);
	}
};