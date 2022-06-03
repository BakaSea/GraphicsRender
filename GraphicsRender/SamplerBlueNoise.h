#pragma once
#include "Sampler.h"

class SamplerBlueNoise : public Sampler {
public:
	SamplerBlueNoise(int samples) : Sampler(samples) {}

protected:
	vector<float>* generatePattern1D(float x) override;
	vector<Vector2f>* generatePattern2D(float x, float y) override;
	vector<Vector3f>* generatePattern3D(float x, float y, float z) override;

private:
	bool check(const vector<Vector2f>& pattern, const Vector2f& point, float radius) const;
};
