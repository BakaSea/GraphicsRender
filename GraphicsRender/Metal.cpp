#include "Metal.h"
#include "MathHelper.h"

bool Metal::scatter(const Ray3f& ray, const HitRecord& hrec, ScatterRecord& srec) const {
    Vector3f reflected = reflect(ray.direction(), hrec.normal);
    srec.ray = Ray3f(hrec.p, reflected + fuzziness * randomInUnitSphere());
    srec.attenuation = albedo->value(hrec.u, hrec.v, hrec.p);
    srec.isSpecular = true;
    srec.pdf = nullptr;
    return true;
}
