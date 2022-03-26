#pragma once
#include "Material.h"
#include "Texture.h"

class Metal : public Material {
public:
	Metal(Texture* albedo, float fuzziness) : albedo(albedo), fuzziness(fuzziness) {}
	~Metal() {
		delete albedo;
	}
	virtual bool scatter(const Ray3f& ray, const HitRecord& hrec, ScatterRecord& srec) const override;

private:
	Texture* albedo;
	float fuzziness;
};