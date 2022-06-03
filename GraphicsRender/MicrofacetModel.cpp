#include "MicrofacetModel.h"
#include <iostream>
using namespace std;

Vector3f MicrofacetModel::BRDF(const HitRecord& hrec, const Vector3f& in, const Vector3f& out) const {
    Vector3f h = normalize(in + out);
    float LoH = fabs(dot(in, h));
    float VoH = fabs(dot(out, h));
    Vector3f color = attenuation->value(hrec.u, hrec.v, hrec.p);
    Vector3f F0 = lerp(baseF0, color, metallic);
    Vector3f F = Fschlick(F0, VoH);
    
    Vector3f kd = attenuation->hasKd() ? attenuation->getKd() : (Vector3f(1, 1, 1) - F) * (1.0f - metallic);
    Vector3f diffuse = color / PI * kd;

    float D = NDF(hrec.normal, h, roughness);
    float G = GF(hrec.normal, in, out);
    float LoN = fabs(dot(in, hrec.normal));
    float VoN = fabs(dot(out, hrec.normal));
    Vector3f ks = attenuation->hasKs() ? attenuation->getKs() : Vector3f(1, 1, 1);
    Vector3f specular = ks * F * D * G / (4 * LoN * VoN);

    Vector3f result = diffuse + specular;
    return result;
}

Vector3f MicrofacetModel::Fschlick(Vector3f F0, float VoH) const {
    return lerp(F0, Vector3f(1, 1, 1), pow(1 - VoH, 5));
}