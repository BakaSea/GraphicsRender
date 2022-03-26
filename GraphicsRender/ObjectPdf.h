#pragma once
#include "Pdf.h"
#include "Object.h"

class ObjectPdf : public Pdf {
public:
	ObjectPdf(Object* object, const Vector3f& origin) : object(object), origin(origin) {}
	float value(const Vector3f& direction) const override;
	Vector3f generate() const override;

private:
	Vector3f origin;
	Object* object;
};

