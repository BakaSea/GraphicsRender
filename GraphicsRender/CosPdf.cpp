#include "CosPdf.h"
#include "MathHelper.h"

CosPdf::CosPdf(const Vector3f& w) {
    uvw.buildFromW(w);
}

float CosPdf::value(const Vector3f& direction) const {
    float cosine = dot(direction, uvw.w());
    if (cosine < 0) cosine = 0;
    return cosine / PI;
}

Vector3f CosPdf::generate() const {
    return uvw.local(randomCosDirection());
}
