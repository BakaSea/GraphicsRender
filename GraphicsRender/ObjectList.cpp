#include "ObjectList.h"
#include "Sampler.h"
#include <iostream>
#include <fstream>
using namespace std;

bool ObjectList::hit(const Ray3f& ray, float tMin, float tMax, HitRecord& record) const {
    bool flag = false;
    HitRecord temp;
    for (int i = 0; i < _size; ++i) {
        if (list[i]->hit(ray, tMin, tMax, temp)) {
            flag = true;
            tMax = temp.t;
            record = temp;
        }
    }
    return flag;
}

bool ObjectList::getBoundingBox(float t0, float t1, AABB& box) const {
    if (size() < 1) return false;
    AABB temp;
    if (!list[0]->getBoundingBox(t0, t1, temp)) return false;
    box = temp;
    for (int i = 1; i < size(); ++i) {
        if (list[i]->getBoundingBox(t0, t1, temp)) {
            box = AABB::getSurroundingBox(box, temp);
        } else return false;
    }
    return true;
}

float ObjectList::pdfValue(const Ray3f& ray) const {
    float sum = 0;
    for (int i = 0; i < _size; ++i) {
        sum += list[i]->pdfWeight() * list[i]->pdfValue(ray) / weightSum;
    }
    return sum;
}

Vector3f ObjectList::random(const Vector3f& origin, Sampler& sampler) const {
    float* cdf = weightCdf;
    float ws = weightSum;
    int sz = _size;
    int index = (int)sampler.generate1D([cdf, ws, sz](float p) -> float {
        for (int i = 0; i < sz; ++i) {
            if (cdf[i] / ws > p) {
                return i;
            }
        }
        return sz - 1;
    });
    return list[index]->random(origin, sampler);
}

float ObjectList::pdfWeight() const {
    return weightSum;
}

void ObjectList::enlarge() {
    Object** temp = new Object * [_capacity];
    float* tempWeightCdf = new float[_capacity];
    for (int i = 0; i < _capacity; ++i) {
        temp[i] = list[i];
        tempWeightCdf[i] = weightCdf[i];
    }
    delete[] list;
    delete[] weightCdf;
    list = new Object * [2 * _capacity];
    weightCdf = new float[2 * _capacity];
    for (int i = 0; i < _capacity; ++i) {
        list[i] = temp[i];
        weightCdf[i] = tempWeightCdf[i];
    }
    delete[] temp;
    delete[] tempWeightCdf;
    _capacity *= 2;
}
