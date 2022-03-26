#pragma once
#include "Pdf.h"
#include "OnB.h"

class CosPdf : public Pdf {
public:
	CosPdf(const Vector3f& w);
	float value(const Vector3f& direction) const override;
	Vector3f generate() const override;

private:
	OnB uvw;
};
