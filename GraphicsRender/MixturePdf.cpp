#include "MixturePdf.h"
#include "MathHelper.h"

float MixturePdf::value(const Vector3f& direction) const {
    return 0.5f * p0->value(direction) + 0.5f * p1->value(direction);
}

Vector3f MixturePdf::generate(Sampler& sampler) const {
    if (frand() < 0.5f) {
        return p0->generate(sampler);
    } else {
        return p1->generate(sampler);
    }
}

Vector3f MixturePdf::generate(Sampler& sampler0, Sampler& sampler1) {
    if (frand() < 0.5f) {
        return p0->generate(sampler0);
    } else {
        return p1->generate(sampler1);
    }
}
