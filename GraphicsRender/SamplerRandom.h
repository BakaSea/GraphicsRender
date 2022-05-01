#pragma once
#include "Sampler.h"

class SamplerRandom : public Sampler {
public:
	SamplerRandom(int samples) : Sampler(samples) {}

protected:
	vector<Vector2f>* generatePattern2D(float x, float y) override;
};

