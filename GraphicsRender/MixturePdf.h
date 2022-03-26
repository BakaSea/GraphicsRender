#pragma once
#include "Pdf.h"

class MixturePdf : public Pdf {
public:
	MixturePdf(Pdf* p0, Pdf* p1) : p0(p0), p1(p1) {}
	float value(const Vector3f& direction) const override;
	Vector3f generate() const override;

private:
	Pdf* p0;
	Pdf* p1;
};
