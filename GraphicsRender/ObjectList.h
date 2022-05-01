#pragma once
#include "Object.h"
#include <vector>
using namespace std;

class ObjectList : public Object {
public:
	ObjectList() : _size(0), _capacity(1) {
		list = new Object * [1];
	}
	~ObjectList() {
		for (int i = 0; i < _size; ++i) {
			delete list[i];
		}
		delete[] list;
	}
	inline Object*& operator [] (int i) {
		return list[i];
	}
	inline Object* operator [] (int i) const {
		return list[i];
	}
	inline int size() const {
		return _size;
	}
	inline void add(Object* object) {
		if (_size == _capacity) {
			enlarge();
		}
		list[_size++] = object;
	}
	inline Object* back() {
		return list[_size - 1];
	}
	inline Object** getList() {
		return list;
	}
	bool hit(const Ray3f& ray, float tMin, float tMax, HitRecord& record) const override;
	bool getBoundingBox(float t0, float t1, AABB& box) const override;
	float pdfValue(const Ray3f& ray) const override;
	Vector3f random(const Vector3f& origin, Sampler &sampler) const override;

private:
	int _size, _capacity;
	Object** list;
	void enlarge();
};

