#pragma once
#include "Material.h"
#include "Texture.h"

class DiffuseLight : public Material {
public:
	DiffuseLight(Texture* emit) : emit(emit) {}
	virtual Vector3f emitted(float u, float v, const Vector3f& p) const override;
private:
	Texture* emit;
};
