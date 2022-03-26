#include "Camera.h"
#include <math.h>

Camera::Camera(const Vector3f& lookFrom, const Vector3f& lookAt, const Vector3f& vup, float vfov, float aspect) {
	Vector3f u, v, w;
	float theta = vfov * float(acos(-1.0)) / 180.0f;
	float halfHeight = tan(theta / 2.0f);
	float halfWidth = aspect * halfHeight;
	origin = lookFrom;
	w = normalize(lookFrom - lookAt);
	u = normalize(cross(vup, w));
	v = cross(w, u);
	lowerLeftCorner = origin - halfWidth * u - halfHeight * v - w;
	horizontal = 2.0f * halfWidth * u;
	vertical = 2.0f * halfHeight * v;
}
