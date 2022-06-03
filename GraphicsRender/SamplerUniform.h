#pragma once
#include "Sampler.h"

class SamplerUniform : public Sampler {
public:
	SamplerUniform(int samples) : Sampler(samples) {}

protected:
	vector<float>* generatePattern1D(float x) override;
	vector<Vector2f>* generatePattern2D(float x, float y) override;
	vector<Vector3f>* generatePattern3D(float x, float y, float z) override;
};
