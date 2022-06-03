#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include <map>
#include <vector>
#include <functional>
using namespace std;

class Sampler {
public:
	Sampler(int samples) : samples(samples) {}
	virtual float generate1D(float x);
	float generate1D(function<float(float)> transform);
	virtual Vector2f generate2D(float x, float y);
	Vector2f generate2D(function<Vector2f(Vector2f)> transform);
	Vector3f generate3D(function<Vector3f(Vector2f)> transform);
	virtual Vector3f generate3D(float x, float y, float z);
	Vector3f generate3D(function<Vector3f(Vector3f)> transform);

protected:
	int samples;
	map<float, vector<float>> patterns1D;
	map<Vector2f, vector<Vector2f>> patterns2D;
	map<Vector3f, vector<Vector3f>> patterns3D;

	virtual vector<float>* generatePattern1D(float x) = 0;
	vector<float>* getPattern1D(float x);
	virtual vector<Vector2f>* generatePattern2D(float x, float y) = 0;
	vector<Vector2f>* getPattern2D(float x, float y);
	virtual vector<Vector3f>* generatePattern3D(float x, float y, float z) = 0;
	vector<Vector3f>* getPattern3D(float x, float y, float z);
};