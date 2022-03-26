#pragma once
#include <math.h>

template<class T>
class Vector3 {
public:
	Vector3(T e0 = 0, T e1 = 0, T e2 = 0) {
		e[0] = e0;
		e[1] = e1;
		e[2] = e2;
	}
	inline T x() const {
		return e[0];
	}
	inline T y() const {
		return e[1];
	}
	inline T z() const {
		return e[2];
	}
	inline const Vector3& operator + () const {
		return *this;
	}
	inline Vector3 operator - () const {
		return Vector3(-e[0], -e[1], -e[2]);
	}
	inline T operator [] (int i) const {
		return e[i];
	}
	inline T& operator [] (int i) {
		return e[i];
	}
	inline T squaredLength() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}
	inline T length() const {
		return T(sqrt(squaredLength()));
	}
	inline Vector3& operator += (const Vector3& v) {
		return *this = *this + v;
	}
	inline Vector3& operator -= (const Vector3& v) {
		return *this = *this - v;
	}
	inline Vector3& operator *= (const Vector3& v) {
		return *this = *this * v;
	}
	inline Vector3& operator /= (const Vector3& v) {
		return *this = *this / v;
	}
	inline Vector3& operator *= (const T& t) {
		return *this = *this * t;
	}
	inline Vector3& operator /= (const T& t) {
		return *this = *this / t;
	}

private:
	T e[3];
};

template<class T>
inline Vector3<T> operator + (const Vector3<T>& v1, const Vector3<T>& v2) {
	return Vector3<T>(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}

template<class T>
inline Vector3<T> operator - (const Vector3<T>& v1, const Vector3<T>& v2) {
	return Vector3<T>(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
}

template<class T>
inline Vector3<T> operator * (const Vector3<T>& v1, const Vector3<T>& v2) {
	return Vector3<T>(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
}

template<class T>
inline Vector3<T> operator / (const Vector3<T>& v1, const Vector3<T>& v2) {
	return Vector3<T>(v1[0] / v2[0], v1[1] / v2[1], v1[2] / v2[2]);
}

template<class T>
inline Vector3<T> operator * (const Vector3<T>& v, const T& t) {
	return Vector3<T>(t * v[0], t * v[1], t * v[2]);
}

template<class T>
inline Vector3<T> operator * (const T& t, const Vector3<T>& v) {
	return v * t;
}

template<class T>
inline Vector3<T> operator / (const Vector3<T>& v, const T& t) {
	return Vector3<T>(v[0] / t, v[1] / t, v[2] / t);
}

template<class T>
inline T dot(const Vector3<T>& v1, const Vector3<T>& v2) {
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

template<class T>
inline Vector3<T> cross(const Vector3<T>& v1, const Vector3<T>& v2) {
	return Vector3<T>(v1[1] * v2[2] - v1[2] * v2[1], v1[2] * v2[0] - v1[0] * v2[2], v1[0] * v2[1] - v1[1] * v2[0]);
}

template<class T>
inline Vector3<T> normalize(const Vector3<T>& v) {
	return v / v.length();
}

typedef Vector3<float> Vector3f;