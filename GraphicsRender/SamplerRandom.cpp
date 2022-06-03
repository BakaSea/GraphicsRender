#include "SamplerRandom.h"
#include "MathHelper.h"

vector<float>* SamplerRandom::generatePattern1D(float x) {
	vector<float> pattern;
	for (int i = 0; i < samples; ++i) {
		pattern.push_back(frand() * x);
	}
	patterns1D[x] = pattern;
	return &patterns1D[x];
}

vector<Vector2f>* SamplerRandom::generatePattern2D(float x, float y) {
	Vector2f size(x, y);
	vector<Vector2f> pattern;
	for (int i = 0; i < samples; ++i) {
		pattern.push_back(Vector2f(frand() * x, frand() * y));
	}
	patterns2D[size] = pattern;
	return &patterns2D[size];
}

vector<Vector3f>* SamplerRandom::generatePattern3D(float x, float y, float z) {
	Vector3f size(x, y, z);
	vector<Vector3f> pattern;
	for (int i = 0; i < samples; ++i) {
		pattern.push_back(Vector3f(frand() * x, frand() * y, frand() * z));
	}
	patterns3D[size] = pattern;
	return &patterns3D[size];
}
