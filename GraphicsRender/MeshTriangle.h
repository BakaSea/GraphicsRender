#pragma once
#include "Object.h"
#include <string>
#include <map>
#include "ObjectList.h"
#include "BVHNode.h"
#include "Texture.h"

class MeshTriangle : public Object {
public:
	MeshTriangle(const string& objPath, const Vector3f& center, const Vector3f& scale, Material* material);
	MeshTriangle(const string& objPath, const Vector3f& center, const Vector3f& scale, map<string, Texture*>& textureMap, vector<Material*>& materialList);
	~MeshTriangle();
	bool hit(const Ray3f& ray, float tMin, float tMax, HitRecord& record) const override;
	bool getBoundingBox(float t0, float t1, AABB& box) const override;
	float pdfValue(const Ray3f& ray) const override;
	Vector3f random(const Vector3f& origin, Sampler& sampler) const override;
	float pdfWeight() const override;

private:
	ObjectList triangleList;
	BVHNode* bvh;
};

