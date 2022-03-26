#pragma once
#include <math.h>

template<class T>
class Vector2 {
public:
	Vector2(T e0 = 0, T e1 = 0) {
		e[0] = e0;
		e[1] = e1;
	}
	inline T x() {
		return e[0];
	}
	inline T y() {
		return e[1];
	}
	inline const Vector2& operator + () const {
		return *this;
	}
	inline Vector2 operator - () const {
		return Vector2(-e[0], -e[1]);
	}
	inline T operator [] (int i) const {
		return e[i];
	}
	inline T& operator [] (int i) {
		return e[i];
	}
	inline T squaredLength() const {
		return e[0] * e[0] + e[1] * e[1];
	}
	inline T length() const {
		return T(sqrt(squaredLength()));
	}
	inline Vector2& operator += (const Vector2& v) {
		return *this = *this + v;
	}
	inline Vector2& operator -= (const Vector2& v) {
		return *this = *this - v;
	}
	inline Vector2& operator *= (const Vector2& v) {
		return *this = *this * v;
	}
	inline Vector2& operator /= (const Vector2& v) {
		return *this = *this / v;
	}
	inline Vector2& operator *= (const T& t) {
		return *this = *this * t;
	}
	inline Vector2& operator /= (const T& t) {
		return *this = *this / t;
	}

private:
	T e[2];
};

template<class T>
inline Vector2<T> operator + (const Vector2<T>& v1, const Vector2<T>& v2) {
	return Vector2<T>(v1[0] + v2[0], v1[1] + v2[1]);
}

template<class T>
inline Vector2<T> operator - (const Vector2<T>& v1, const Vector2<T>& v2) {
	return Vector2<T>(v1[0] - v2[0], v1[1] - v2[1]);
}

template<class T>
inline Vector2<T> operator * (const Vector2<T>& v1, const Vector2<T>& v2) {
	return Vector2<T>(v1[0] * v2[0], v1[1] * v2[1]);
}

template<class T>
inline Vector2<T> operator / (const Vector2<T>& v1, const Vector2<T>& v2) {
	return Vector2<T>(v1[0] / v2[0], v1[1] / v2[1]);
}

template<class T>
inline Vector2<T> operator * (const Vector2<T>& v, const T& t) {
	return Vector2<T>(t * v[0], t * v[1]);
}

template<class T>
inline Vector2<T> operator * (const T& t, const Vector2<T>& v) {
	return v * t;
}

template<class T>
inline Vector2<T> operator / (const Vector2<T>& v, const T& t) {
	return Vector2<T>(v[0] / t, v[1] / t);
}

template<class T>
inline T dot(const Vector2<T>& v1, const Vector2<T>& v2) {
	return v1[0] * v2[0] + v1[1] * v2[1];
}

template<class T>
inline Vector2<T> cross(const Vector2<T>& v1, const Vector2<T>& v2) {
	return v1[0] * v2[1] - v1[1] * v2[0];
}

template<class T>
inline Vector2<T> normalize(const Vector2<T>& v) {
	return v / v.length();
}

typedef Vector2<float> Vector2f;