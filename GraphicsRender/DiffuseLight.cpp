#include "DiffuseLight.h"

Vector3f DiffuseLight::emitted(float u, float v, const Vector3f& p) const {
	return emit->value(u, v, p);
}
