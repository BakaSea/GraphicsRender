#include "TriPyramid.h"

TriPyramid::TriPyramid(const Vector3f& v0, const Vector3f& v1, const Vector3f& v2, const Vector3f& v3, Material* material) : material(material) {
	tri[0] = Triangle(v0, v1, v2, material);
	tri[1] = Triangle(v0, v2, v3, material);
	tri[2] = Triangle(v0, v3, v1, material);
	tri[3] = Triangle(v2, v1, v3, material);
}

bool TriPyramid::hit(const Ray3f& ray, float tMin, float tMax, HitRecord& record) const {
	bool flag = false;
	HitRecord temp;
	for (int i = 0; i < 4; ++i) {
		if (tri[i].hit(ray, tMin, tMax, temp)) {
			flag = true;
			tMax = temp.t;
			record = temp;
		}
	}
	return flag;
}

bool TriPyramid::getBoundingBox(float t0, float t1, AABB& box) const {
	tri[0].getBoundingBox(t0, t1, box);
	AABB temp;
	for (int i = 1; i < 4; ++i) {
		tri[i].getBoundingBox(t0, t1, temp);
		box = AABB::getSurroundingBox(box, temp);
	}
	return true;
}
