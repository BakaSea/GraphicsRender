#pragma once
#include "Vector3.h"
#include "Sampler.h"

class Pdf {
public:
	virtual float value(const Vector3f& direction) const = 0;
	virtual Vector3f generate(Sampler& sampler) const = 0;
};