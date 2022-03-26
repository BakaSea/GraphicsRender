#include "MixturePdf.h"
#include "MathHelper.h"

float MixturePdf::value(const Vector3f& direction) const {
    return 0.5f * p0->value(direction) + 0.5f * p1->value(direction);
}

Vector3f MixturePdf::generate() const {
    if (frand() < 0.5f) {
        return p0->generate();
    } else {
        return p1->generate();
    }
}
