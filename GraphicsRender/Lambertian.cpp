#include "Lambertian.h"
#include "MathHelper.h"
#include "CosPdf.h"

bool Lambertian::scatter(const Ray3f& ray, const HitRecord& hrec, ScatterRecord& srec) const {
    srec.isSpecular = false;
    srec.attenuation = albedo->value(hrec.u, hrec.v, hrec.p);
    srec.pdf = new CosPdf(hrec.normal);
    return true;
}

Vector3f Lambertian::BRDF(const HitRecord& hrec) const {
    return albedo->value(hrec.u, hrec.v, hrec.p) / PI;
}
