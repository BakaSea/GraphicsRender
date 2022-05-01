#pragma once
#include "Vector2.h"
#include <map>
#include <vector>
#include <mutex>
using namespace std;

class Sampler {
public:
	Sampler(int samples) : samples(samples) {}
	Vector2f generate2D(float x, float y);

protected:
	mutex mut;
	int samples;
	map<pair<float, float>, vector<Vector2f>> patterns2D;

	virtual vector<Vector2f>* generatePattern2D(float x, float y) = 0;
	vector<Vector2f>* getPattern2D(float x, float y);
};