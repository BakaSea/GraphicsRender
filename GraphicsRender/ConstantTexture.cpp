#include "ConstantTexture.h"

Vector3f ConstantTexture::value(float u, float v, const Vector3f& p) const {
    return color;
}
