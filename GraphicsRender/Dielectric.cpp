#include "Dielectric.h"
#include "MathHelper.h"

bool Dielectric::scatter(const Ray3f& ray, const HitRecord& hrec, ScatterRecord& srec) const {
    Vector3f outNormal;
    Vector3f reflected = reflect(ray.direction(), hrec.normal);
    Vector3f refracted;
    float r;
    srec.attenuation = Vector3f(1, 1, 1);
    float reflectProb;
    float cosine;
    if (dot(ray.direction(), hrec.normal) > 0) {
        outNormal = -hrec.normal;
        r = ref;
        cosine = ref * dot(ray.direction(), hrec.normal);
    } else {
        outNormal = hrec.normal;
        r = 1.0f / ref;
        cosine = -dot(ray.direction(), hrec.normal);
    }
    if (refract(ray.direction(), outNormal, r, refracted)) {
        reflectProb = schlick(cosine, ref);
    } else {
        reflectProb = 1.0f;
    }
    if (frand() < reflectProb) {
        srec.ray = Ray3f(hrec.p, reflected);
    } else {
        srec.ray = Ray3f(hrec.p, refracted);
    }
    srec.isSpecular = true;
    srec.pdf = nullptr;
    return true;
}
