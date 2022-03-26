#pragma once
#include "MathHelper.h"
#include "Ray.h"

class AABB {
public:
	AABB() {}
	AABB(const Vector3f& A, const Vector3f& B) : A(A), B(B) {}
	inline Vector3f getMin() {
		return A;
	}
	inline Vector3f getMax() {
		return B;
	}
	bool hit(const Ray3f& ray, float tMin, float tMax) const;
	inline static AABB getSurroundingBox(const AABB& b0, const AABB& b1) {
		Vector3f small(ffmin(b0.A.x(), b1.A.x()),
			ffmin(b0.A.y(), b1.A.y()),
			ffmin(b0.A.z(), b1.A.z()));
		Vector3f big(ffmax(b0.B.x(), b1.B.x()),
			ffmax(b0.B.y(), b1.B.y()),
			ffmax(b0.B.z(), b1.B.z()));
		return AABB(small, big);
	}
private:
	Vector3f A;
	Vector3f B;
};