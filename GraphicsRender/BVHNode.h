#pragma once
#include "Object.h"
#include <vector>
using namespace std;

class BVHNode : public Object {
public:
	BVHNode() : left(nullptr), right(nullptr) {}
	~BVHNode();
	BVHNode(Object** list, int size, float t0, float t1);
	bool hit(const Ray3f& ray, float tMin, float tMax, HitRecord& record) const override;
	bool getBoundingBox(float t0, float t1, AABB& box) const override;

private:
	Object* left;
	Object* right;
	AABB box;
	static bool cmpX(const Object* A, const Object* B);
	static bool cmpY(const Object* A, const Object* B);
	static bool cmpZ(const Object* A, const Object* B);
};

