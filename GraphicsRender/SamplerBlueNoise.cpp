#include "SamplerBlueNoise.h"
#include "MathHelper.h"

vector<float>* SamplerBlueNoise::generatePattern1D(float x) {
    vector<float> pattern;
    for (int i = 0; i < samples; ++i) {
        pattern.push_back(frand() * x);
    }
    patterns1D[x] = pattern;
    return &patterns1D[x];
}

vector<Vector2f>* SamplerBlueNoise::generatePattern2D(float x, float y) {
    Vector2f size(x, y);
    vector<Vector2f> pattern;
    float radius = sqrt(x * y / (2 * sqrt(3) * (float)samples));
    for (int i = 0; i < samples; ++i) {
        Vector2f point;
        do {
            point[0] = frand() * x;
            point[1] = frand() * y;
        } while (!check(pattern, point, radius));
        pattern.push_back(point);
    }
    patterns2D[size] = pattern;
    return &patterns2D[size];
}

vector<Vector3f>* SamplerBlueNoise::generatePattern3D(float x, float y, float z) {
    return nullptr;
}

bool SamplerBlueNoise::check(const vector<Vector2f>& pattern, const Vector2f& point, float radius) const {
    for (int i = 0; i < pattern.size(); ++i) {
        if ((pattern[i] - point).length() <= radius) return false;
    }
    return true;
}
