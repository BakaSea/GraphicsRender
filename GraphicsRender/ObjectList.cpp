#include "ObjectList.h"
#include "assert.h"

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
    float w = 1.0f / size();
    float sum = 0;
    for (int i = 0; i < _size; ++i) {
        sum += w * list[i]->pdfValue(ray);
    }
    return sum;
}

Vector3f ObjectList::random(const Vector3f& origin) const {
    int index = int(frand() * size());
    return list[index]->random(origin);
}

void ObjectList::enlarge() {
    Object** temp = new Object * [_capacity];
    for (int i = 0; i < _capacity; ++i) {
        temp[i] = list[i];
    }
    delete[] list;
    list = new Object * [2 * _capacity];
    for (int i = 0; i < _capacity; ++i) {
        list[i] = temp[i];
    }
    delete[] temp;
    _capacity *= 2;
}
