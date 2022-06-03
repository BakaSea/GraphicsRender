#pragma once
#include "MicrofacetModel.h"

class GGX : public MicrofacetModel {
public:
	GGX(Texture* attenuation, Vector3f baseF0, float metallic, float roughness)
		: MicrofacetModel(attenuation, baseF0, metallic, roughness) {
	}
	bool scatter(const Ray3f& ray, const HitRecord& hrec, ScatterRecord& srec) const override;

protected:
	float NDF(const Vector3f& n, const Vector3f& h, float alpha) const;
	float GF(const Vector3f& n, const Vector3f& in, const Vector3f& out) const;

private:
	float GGXschlick(float NoV, float k) const;
};
