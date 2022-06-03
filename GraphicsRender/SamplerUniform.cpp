#include "SamplerUniform.h"

vector<float>* SamplerUniform::generatePattern1D(float x) {
    vector<float> pattern;
    float dis = x / ((float)samples + 1.0f);
    float s = dis;
    for (int i = 0; i < samples; ++i) {
        pattern.push_back(s);
        s += dis;
    }
    patterns1D[x] = pattern;
    return &patterns1D[x];
}

vector<Vector2f>* SamplerUniform::generatePattern2D(float x, float y) {
    int spa = sqrt(samples);
    Vector2f size(x, y);
    vector<Vector2f> pattern;
    float disX = x / ((float)spa + 1.0f), disY = y / ((float)spa + 1.0f);
    float sx = disX, sy = disY;
    for (int i = 1; i <= spa; ++i) {
        sy = disY;
        for (int j = 1; j <= spa; ++j) {
            pattern.push_back(Vector2f(sx, sy));
            sy += disY;
        }
        sx += disX;
    }
    patterns2D[size] = pattern;
    return &patterns2D[size];
}

vector<Vector3f>* SamplerUniform::generatePattern3D(float x, float y, float z) {
    return nullptr;
}
