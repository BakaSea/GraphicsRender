#pragma once
#include "Object.h"

class RectangleXY : public Object {
public:
	RectangleXY() : x0(0), x1(0), y0(0), y1(0), z(0), material(nullptr) {}
	RectangleXY(float x0, float x1, float y0, float y1, float z, Material* material) : x0(x0), x1(x1), y0(y0), y1(y1), z(z), material(material) {}
	bool hit(const Ray3f& ray, float tMin, float tMax, HitRecord& record) const override;
	bool getBoundingBox(float t0, float t1, AABB& box) const override;

private:
	float x0, x1, y0, y1, z;
	Material* material;
};

class RectangleXZ : public Object {
public:
	RectangleXZ() : x0(0), x1(0), z0(0), z1(0), y(0), material(nullptr) {}
	RectangleXZ(float x0, float x1, float z0, float z1, float y, Material* material) : x0(x0), x1(x1), z0(z0), z1(z1), y(y), material(material) {}
	bool hit(const Ray3f& ray, float tMin, float tMax, HitRecord& record) const override;
	bool getBoundingBox(float t0, float t1, AABB& box) const override;

private:
	float x0, x1, z0, z1, y;
	Material* material;
};

class RectangleYZ : public Object {
public:
	RectangleYZ() : y0(0), y1(0), z0(0), z1(0), x(0), material(nullptr) {}
	RectangleYZ(float y0, float y1, float z0, float z1, float x, Material* material) : y0(y0), y1(y1), z0(z0), z1(z1), x(x), material(material) {}
	bool hit(const Ray3f& ray, float tMin, float tMax, HitRecord& record) const override;
	bool getBoundingBox(float t0, float t1, AABB& box) const override;

private:
	float y0, y1, z0, z1, x;
	Material* material;
};