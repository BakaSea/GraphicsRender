#include "Sampler.h"
#include "MathHelper.h"

Vector2f Sampler::generate2D(float x, float y) {
    vector<Vector2f>* pattern = getPattern2D(x, y);
    if (pattern == nullptr) {
        mut.lock();
        pattern = generatePattern2D(x, y);
        mut.unlock();
    }
    int index = irand(pattern->size());
    return (*pattern)[index];
}

vector<Vector2f>* Sampler::getPattern2D(float x, float y) {
    pair<float, float> size = make_pair(x, y);
    auto iter = patterns2D.find(size);
    if (iter == patterns2D.end()) return nullptr;
    return &iter->second;
}
