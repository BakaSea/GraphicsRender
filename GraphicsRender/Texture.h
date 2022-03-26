#pragma once
#include "Vector3.h"

class Texture {
public:
	virtual Vector3f value(float u, float v, const Vector3f& p) const = 0;
};