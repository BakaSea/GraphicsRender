#pragma once
#include <memory>
#include "Ray.h"
#include "Object.h"
#include "Pdf.h"

struct HitRecord;

struct ScatterRecord {
	Ray3f ray;
	bool isSpecular;
	Vector3f attenuation;
	Pdf* pdf;
	ScatterRecord() : isSpecular(false), pdf(nullptr) {}
	~ScatterRecord() {
		delete pdf;
	}
};

class Material {
public:
	virtual bool scatter(const Ray3f& ray, const HitRecord& hrec, ScatterRecord& srec) const {
		return false;
	}
	virtual float scatteringPdf(const Ray3f& ray, const HitRecord& record, const Ray3f& scattered) const {
		return false;
	}
	virtual Vector3f emitted(float u, float v, const Vector3f& p) const {
		return Vector3f(0, 0, 0);
	}
};