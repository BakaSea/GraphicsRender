#include "MathHelper.h"

default_random_engine randEngine;

Vector3f transformCosDirection(Vector2f point) {
	float r1 = point.x();
	float r2 = point.y();
	float z = float(sqrt(1 - r2));
	float phi = 2 * PI * r1;
	float x = float(cos(phi)) * 2 * float(sqrt(r2));
	float y = float(sin(phi)) * 2 * float(sqrt(r2));
	return Vector3f(x, y, z);
}