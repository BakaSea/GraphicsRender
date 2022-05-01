#include "SamplerUniform.h"

vector<Vector2f>* SamplerUniform::generatePattern2D(float x, float y) {
    int spa = sqrt(samples);
    pair<float, float> size = make_pair(x, y);
    vector<Vector2f> pattern;
    if (spa == 1) {
        pattern.push_back(Vector2f(x / 2.0f, y / 2.0f));
        patterns2D[size] = pattern;
        return &patterns2D[size];
    } else {
        float disX = x / ((float)spa - 1.0f), disY = y / ((float)spa - 1.0f);
        float sx = 0, sy = 0.;
        for (int i = 1; i <= spa; ++i) {
            sy = 0;
            for (int j = 1; j <= spa; ++j) {
                pattern.push_back(Vector2f(sx, sy));
                sy += disY;
            }
            sx += disX;
        }
        patterns2D[size] = pattern;
        return &patterns2D[size];
    }
}
