#include "Sampler.h"
#include "MathHelper.h"
#include <iostream>
using namespace std;

float Sampler::generate1D(float x) {
    vector<float>* pattern = getPattern1D(x);
    if (pattern == nullptr) {
        pattern = generatePattern1D(x);
    }
    int index = irand(pattern->size());
    return (*pattern)[index];
}

float Sampler::generate1D(function<float(float)> transform) {
    return transform(generate1D(1));
}

Vector2f Sampler::generate2D(float x, float y) {
    vector<Vector2f>* pattern = getPattern2D(x, y);
    if (pattern == nullptr) {
        pattern = generatePattern2D(x, y);
    }
    int index = irand(pattern->size());
    return (*pattern)[index];
}

Vector2f Sampler::generate2D(function<Vector2f(Vector2f)> transform) {
    return transform(generate2D(1, 1));
}

Vector3f Sampler::generate3D(function<Vector3f(Vector2f)> transform) {
    return transform(generate2D(1, 1));
}

Vector3f Sampler::generate3D(float x, float y, float z) {
    vector<Vector3f>* pattern = getPattern3D(x, y, z);
    if (pattern == nullptr) {
        pattern = generatePattern3D(x, y, z);
    }
    int index = irand(pattern->size());
    return (*pattern)[index];
}

Vector3f Sampler::generate3D(function<Vector3f(Vector3f)> transform) {
    return transform(generate3D(1, 1, 1));
}

vector<float>* Sampler::getPattern1D(float x) {
    auto iter = patterns1D.find(x);
    if (iter == patterns1D.end()) return nullptr;
    return &iter->second;
}

vector<Vector2f>* Sampler::getPattern2D(float x, float y) {
    Vector2f size = Vector2f(x, y);
    auto iter = patterns2D.find(size);
    if (iter == patterns2D.end()) return nullptr;
    return &iter->second;
}

vector<Vector3f>* Sampler::getPattern3D(float x, float y, float z) {
    Vector3f size = Vector3f(x, y, z);
    auto iter = patterns3D.find(size);
    if (iter == patterns3D.end()) return nullptr;
    return &iter->second;
}
