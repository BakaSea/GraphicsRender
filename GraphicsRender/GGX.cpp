#include "GGX.h"
#include "GGXPdf.h"

bool GGX::scatter(const Ray3f& ray, const HitRecord& hrec, ScatterRecord& srec) const {
    srec.pdf = new GGXPdf(-ray.direction(), hrec.normal, roughness);
    return true;
}

float GGX::NDF(const Vector3f& n, const Vector3f& h, float alpha) const {
    float NoH = fabs(dot(n, h));
    float a2 = alpha * alpha;
    float x = NoH * NoH * (a2 - 1.0f) + 1.0f;
    return a2 / (PI * x * x);
}

float GGX::GF(const Vector3f& n, const Vector3f& in, const Vector3f& out) const {
    float NoL = fabs(dot(n, in));
    float NoV = fabs(dot(n, out));
    float k = (roughness + 1.0f) * (roughness + 1.0f) / 8.0f;
    return GGXschlick(NoL, k) * GGXschlick(NoV, k);
}

float GGX::GGXschlick(float NoV, float k) const {
    return NoV / (lerp(k, 1, NoV));
}
