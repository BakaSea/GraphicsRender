#pragma once
#include <stdlib.h>
#include "Vector3.h"
#include "Vector2.h"

const float PI = float(acos(-1.0));

inline static float frand() {
	return float(rand()) / (float(RAND_MAX)+1.0f);
}

inline static int irand(int mod) {
	return rand() % mod;
}

inline Vector3f randomInUnitSphere() {
	Vector3f p;
	do {
		p = 2.0f * Vector3f(frand(), frand(), frand()) - Vector3f(1, 1, 1);
	} while (dot(p, p) >= 1.0f);
	return normalize(p);
}

inline Vector3f reflect(const Vector3f& v, const Vector3f& n) {
	Vector3f nv = normalize(v);
	return nv - 2 * dot(nv, n) * n;
}

inline bool refract(const Vector3f& v, const Vector3f& n, float ref, Vector3f& refracted) {
	Vector3f nv = normalize(v);
	float c = dot(nv, n);
	float delta = 1.0f - ref * ref * (1.0f - c * c);
	if (delta > 0) {
		refracted = ref * (nv - n * c) - n * float(sqrt(delta));
		return true;
	} else return false;
}

inline float schlick(float cosine, float ref) {
	float r0 = (1.0f - ref) / (1.0f + ref);
	r0 = r0 * r0;
	return r0 + (1.0f - r0) * float(pow(1.0f - cosine, 5.0f));
}

inline Vector3f solveNaN(const Vector3f& v) {
	Vector3f res = v;
	if (!(res[0] == res[0])) res[0] = 0;
	if (!(res[1] == res[1])) res[1] = 0;
	if (!(res[2] == res[2])) res[2] = 0;
	return res;
}

inline float ffmin(float a, float b) {
	return a < b ? a : b;
}

inline float ffmax(float a, float b) {
	return a > b ? a : b;
}

inline void swap(float& a, float& b) {
	float c = a;
	a = b;
	b = c;
}

inline Vector3f randomCosDirection() {
	float r1 = frand();
	float r2 = frand();
	float z = float(sqrt(1 - r2));
	float phi = 2 * PI * r1;
	float x = float(cos(phi)) * 2 * float(sqrt(r2));
	float y = float(sin(phi)) * 2 * float(sqrt(r2));
	return Vector3f(x, y, z);
}

inline Vector2f randomInUnitCircle() {
	Vector2f p;
	do {
		p = 2.0f * Vector2f(frand(), frand()) - Vector2f(1, 1);
	} while (dot(p, p) >= 1.0f);
	return normalize(p);
}