#include "ObjectPdf.h"

float ObjectPdf::value(const Vector3f& direction) const {
    return object->pdfValue(Ray3f(origin, direction));
}

Vector3f ObjectPdf::generate() const {
    return object->random(origin);
}
