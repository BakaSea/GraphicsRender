#pragma once
#include "Material.h"

class Dielectric : public Material {
public:
	Dielectric(float ref) : ref(ref) {}
	virtual bool scatter(const Ray3f& ray, const HitRecord& hrec, ScatterRecord& srec) const override;

private:
	float ref;
};

