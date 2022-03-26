#pragma once
#include "Texture.h"

class ConstantTexture : public Texture {
public:
	ConstantTexture(const Vector3f& color) : color(color) {}
	Vector3f value(float u, float v, const Vector3f& p) const override;

private:
	Vector3f color;
};
