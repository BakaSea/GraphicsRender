#include "Lambertian.h"
#include "MathHelper.h"
#include "CosPdf.h"

bool Lambertian::scatter(const Ray3f& ray, const HitRecord& hrec, ScatterRecord& srec) const {
    srec.isSpecular = false;
    srec.attenuation = albedo->value(hrec.u, hrec.v, hrec.p);
    srec.pdf = new CosPdf(hrec.normal);
    return true;
}

float Lambertian::scatteringPdf(const Ray3f& ray, const HitRecord& record, const Ray3f& scattered) const {
    float cosine = dot(record.normal, scattered.direction());
    if (cosine < 0) return 0;
    else return cosine / PI;
}
