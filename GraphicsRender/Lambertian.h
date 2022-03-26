#pragma once
#include "Material.h"
#include "Texture.h"

class Lambertian : public Material {
public:
	Lambertian(Texture* albedo) : albedo(albedo) {}
	~Lambertian() {
		delete albedo;
	}
	virtual bool scatter(const Ray3f& ray, const HitRecord& hrec, ScatterRecord& srec) const override;
	virtual float scatteringPdf(const Ray3f& ray, const HitRecord& record, const Ray3f& scattered) const override;

private:
	Texture* albedo;
};

