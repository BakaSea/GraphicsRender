#pragma once
#include "Sampler.h"

class SamplerBlueNoise : public Sampler {
public:
	SamplerBlueNoise(int samples) : Sampler(samples) {}

protected:
	vector<Vector2f>* generatePattern2D(float x, float y) override;

private:
	bool check(const vector<Vector2f>& pattern, const Vector2f& point, float radius) const;
};
