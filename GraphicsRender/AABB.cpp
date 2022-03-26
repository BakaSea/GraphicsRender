#include "AABB.h"

bool AABB::hit(const Ray3f& ray, float tMin, float tMax) const {
	for (int i = 0; i < 3; ++i) {
		float inv = 1.0f / ray.direction()[i];
		float t0 = (A[i] - ray.origin()[i]) * inv;
		float t1 = (B[i] - ray.origin()[i]) * inv;
		if (inv < 0.0f) {
			swap(t0, t1);
		}
		tMin = ffmax(t0, tMin);
		tMax = ffmin(t1, tMax);
		if (tMax <= tMin) return false;
	}
	return true;
}
