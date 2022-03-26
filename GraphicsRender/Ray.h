#pragma once
#include "Vector3.h"

template<class T, class S>
class Ray {
public:
	Ray() {}
	Ray(const T& a, const T& b) : A(a), B(normalize(b)) {}
	T origin() const {
		return A;
	}
	T direction() const {
		return B;
	}
	T point(S t) const {
		return A + t * B;
	}
private:
	T A, B;
};

typedef Ray<Vector3f, float> Ray3f;