#pragma once
#include "Pdf.h"
#include "OnB.h"

class GGXPdf : public Pdf {
public:
	GGXPdf(const Vector3f& out, const Vector3f& n, float alpha) : out(out), alpha(alpha) {
		uvw.buildFromW(n);
	}
	float value(const Vector3f& direction) const override;
	Vector3f generate(Sampler& sampler) const override;

private:
	float alpha;
	Vector3f out;
	OnB uvw;
};

