#pragma once
#include "Sampler.h"

class SamplerUniform : public Sampler {
public:
	SamplerUniform(int samples) : Sampler(samples) {}

protected:
	vector<Vector2f>* generatePattern2D(float x, float y) override;
};
