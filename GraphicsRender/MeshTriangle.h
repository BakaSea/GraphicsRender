#pragma once
#include "Object.h"
#include <string>
#include <map>
#include "ObjectList.h"
#include "BVHNode.h"

class MeshTriangle : public Object {
public:
	MeshTriangle(const string& objPath, const Vector3f& center, const Vector3f& scale, Material* material);
	MeshTriangle(const string& objPath, const Vector3f& center, const Vector3f& scale, map<string, Material*> materialMap);
	~MeshTriangle();
	bool hit(const Ray3f& ray, float tMin, float tMax, HitRecord& record) const override;
	bool getBoundingBox(float t0, float t1, AABB& box) const override;

private:
	ObjectList triangleList;
	BVHNode* bvh;
};

