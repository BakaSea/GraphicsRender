#pragma once
#include "Vector3.h"
#include "Ray.h"

class Camera {
public:
	Camera(const Vector3f& lookFrom, const Vector3f& lookAt, const Vector3f& vup, float vfov, float aspect);
	Ray3f getRay(float u, float v) {
		return Ray3f(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
	}

private:
	Vector3f origin;
	Vector3f lowerLeftCorner;
	Vector3f horizontal;
	Vector3f vertical;
};