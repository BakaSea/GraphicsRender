#include "SamplerRandomNP.h"
#include "MathHelper.h"

float SamplerRandomNP::generate1D(float x) {
    return frand() * x;
}

Vector2f SamplerRandomNP::generate2D(float x, float y) {
    return Vector2f(frand() * x, frand() * y);
}

Vector3f SamplerRandomNP::generate3D(float x, float y, float z) {
    return Vector3f(frand() * x, frand() * y, frand() * z);
}
