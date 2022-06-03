#pragma once
#include <memory>
#include "Ray.h"
#include "Object.h"
#include "Pdf.h"

struct HitRecord;

struct ScatterRecord {
	Pdf* pdf;
	ScatterRecord() : pdf(nullptr) {}
	~ScatterRecord() {
		delete pdf;
	}
};

class Material {
public:
	virtual bool scatter(const Ray3f& ray, const HitRecord& hrec, ScatterRecord& srec) const {
		return false;
	}
	virtual Vector3f emitted(float u, float v, const Vector3f& p) const {
		return Vector3f(0, 0, 0);
	}
	virtual Vector3f BRDF(const HitRecord& hrec, const Vector3f& in, const Vector3f& out) const {
		return 0.0f;
	}
};