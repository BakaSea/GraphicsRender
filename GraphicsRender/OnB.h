#pragma once
#include "Vector3.h"

class OnB {
public:
	OnB() {}
	inline Vector3f operator [] (int i) const {
		return axis[i];
	}
	Vector3f u() const {
		return axis[0];
	}
	Vector3f v() const {
		return axis[1];
	}
	Vector3f w() const {
		return axis[2];
	}
	Vector3f local(float a, float b, float c) const {
		return a * u() + b * v() + c * w();
	}
	Vector3f local(const Vector3f& vec) const {
		return vec.x() * u() + vec.y() * v() + vec.z() * w();
	}
	void buildFromW(const Vector3f& vec) {
		axis[2] = normalize(vec);
		Vector3f a;
		if (fabs(w().x()) > 0.9) a = Vector3f(0, 1, 0);
		else a = Vector3f(1, 0, 0);
		axis[1] = normalize(cross(w(), a));
		axis[0] = cross(w(), v());
	}

private:
	Vector3f axis[3];
};
