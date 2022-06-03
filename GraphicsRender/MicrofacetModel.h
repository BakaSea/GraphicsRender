#pragma once
#include "Material.h"
#include "Texture.h"

class MicrofacetModel : public Material {
public:
	MicrofacetModel(Texture* attenuation, Vector3f baseF0, float metallic, float roughness)
		: attenuation(attenuation), baseF0(baseF0), metallic(metallic), roughness(roughness) {}
	~MicrofacetModel() {
		delete attenuation;
	}
	virtual Vector3f BRDF(const HitRecord& hrec, const Vector3f& in, const Vector3f& out) const override;

protected:
	Texture* attenuation;
	Vector3f baseF0;
	float metallic, roughness;
	
	Vector3f Fschlick(Vector3f F0, float LoH) const;
	virtual float NDF(const Vector3f& n, const Vector3f& h, float alpha) const = 0;
	virtual float GF(const Vector3f& n, const Vector3f& in, const Vector3f& out) const = 0;
};

