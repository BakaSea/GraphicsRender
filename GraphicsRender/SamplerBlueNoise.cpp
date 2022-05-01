#include "SamplerBlueNoise.h"
#include "MathHelper.h"

vector<Vector2f>* SamplerBlueNoise::generatePattern2D(float x, float y) {
    pair<float, float> size = make_pair(x, y);
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

bool SamplerBlueNoise::check(const vector<Vector2f>& pattern, const Vector2f& point, float radius) const {
    for (int i = 0; i < pattern.size(); ++i) {
        if ((pattern[i] - point).length() <= radius) return false;
    }
    return true;
}
