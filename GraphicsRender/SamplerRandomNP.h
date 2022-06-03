#pragma once
#include "Sampler.h"
class SamplerRandomNP : public Sampler {
public:
	SamplerRandomNP() : Sampler(0) {}
	float generate1D(float x) override;
	Vector2f generate2D(float x, float y) override;
	Vector3f generate3D(float x, float y, float z) override;

protected:
	vector<float>* generatePattern1D(float x) override {
		return nullptr;
	}
	vector<Vector2f>* generatePattern2D(float x, float y) override {
		return nullptr;
	}
	vector<Vector3f>* generatePattern3D(float x, float y, float z) override {
		return nullptr;
	}
};

