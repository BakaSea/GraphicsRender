#include "SamplerRandom.h"
#include "MathHelper.h"

vector<Vector2f>* SamplerRandom::generatePattern2D(float x, float y) {
	pair<float, float> size = make_pair(x, y);
	vector<Vector2f> pattern;
	for (int i = 0; i < samples; ++i) {
		pattern.push_back(Vector2f(frand() * x, frand() * y));
	}
	patterns2D[size] = pattern;
	return &patterns2D[size];
}
