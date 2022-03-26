#include "BVHNode.h"
#include <iostream>
#include <algorithm>

BVHNode::~BVHNode() {
    if (dynamic_cast<BVHNode*>(left)) {
        delete left;
    }
    if (dynamic_cast<BVHNode*>(right)) {
        delete right;
    }
}

BVHNode::BVHNode(Object** list, int size, float t0, float t1) {
    int axis = irand(3);
    if (axis == 0) {
        sort(list, list + size, cmpX);
    } else if (axis == 1) {
        sort(list, list + size, cmpY);
    } else {
        sort(list, list + size, cmpZ);
    }
    if (size == 1) {
        left = right = list[0];
    } else if (size == 2) {
        left = list[0];
        right = list[1];
    } else {
        left = new BVHNode(list, size / 2, t0, t1);
        right = new BVHNode(list + size / 2, size - size / 2, t0, t1);
    }
    AABB boxLeft, boxRight;
    if (!left->getBoundingBox(t0, t1, boxLeft) || !right->getBoundingBox(t0, t1, boxRight)) {
        cerr << "No bounding box in BVH node constructor!" << endl;
    }
    box = AABB::getSurroundingBox(boxLeft, boxRight);
}

bool BVHNode::hit(const Ray3f& ray, float tMin, float tMax, HitRecord& record) const {
    if (box.hit(ray, tMin, tMax)) {
        HitRecord recLeft, recRight;
        bool flag = false;
        bool hitLeft = left->hit(ray, tMin, tMax, recLeft);
        if (hitLeft) {
            record = recLeft;
            tMax = recLeft.t;
            flag = true;
        }
        bool hitRight = right->hit(ray, tMin, tMax, recRight);
        if (hitRight) {
            record = recRight;
            flag = true;
        }
        return flag;
    }
    return false;
}

bool BVHNode::getBoundingBox(float t0, float t1, AABB& box) const {
    box = this->box;
    return true;
}

bool BVHNode::cmpX(const Object* A, const Object* B) {
    AABB boxLeft, boxRight;
    if (!A->getBoundingBox(0, 0, boxLeft) || !(B->getBoundingBox(0, 0, boxRight))) {
        cerr << "No bounding box in BVH node constructor!" << endl;
    }
    return boxLeft.getMin().x() - boxRight.getMin().x() < 0.0f;
}

bool BVHNode::cmpY(const Object* A, const Object* B) {
    AABB boxLeft, boxRight;
    if (!A->getBoundingBox(0, 0, boxLeft) || !(B->getBoundingBox(0, 0, boxRight))) {
        cerr << "No bounding box in BVH node constructor!" << endl;
    }
    return boxLeft.getMin().y() - boxRight.getMin().y() < 0.0f;
}

bool BVHNode::cmpZ(const Object* A, const Object* B) {
    AABB boxLeft, boxRight;
    if (!A->getBoundingBox(0, 0, boxLeft) || !(B->getBoundingBox(0, 0, boxRight))) {
        cerr << "No bounding box in BVH node constructor!" << endl;
    }
    return boxLeft.getMin().z() - boxRight.getMin().z() < 0.0f;
}
