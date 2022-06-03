#include "GGXPdf.h"
#include "MathHelper.h"
#include <iostream>
using namespace std;

float GGXPdf::value(const Vector3f& direction) const {
    Vector3f h = normalize(out + direction);
    float NoH = fabs(dot(uvw.w(), h));
    float VoH = fabs(dot(h, out));
    float a2 = alpha * alpha;
    float x = (a2 - 1.0f) * NoH * NoH + 1.0f;
    return a2 * NoH / (PI * x * x) / (4 * VoH);
}

Vector3f GGXPdf::generate(Sampler& sampler) const {
    float a = alpha;
    Vector3f h, res;
    h = uvw.local(sampler.generate3D([a](Vector2f point) -> Vector3f {
        float phi = 2 * PI * point.x();
        float cosTheta = sqrt((1 - point.y()) / (1 + (a * a - 1) * point.y()));
        float sinTheta = sqrt(1 - cosTheta * cosTheta);
        float x = sinTheta * cos(phi);
        float y = sinTheta * sin(phi);
        float z = cosTheta;
        return Vector3f(x, y, z);
    }));
    res = reflect(-out, h);
    return res;
}
