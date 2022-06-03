#pragma once
#include "Vector3.h"

class Texture {
public:
	Texture() : enableKd(false), enableKs(false) {}
	virtual Vector3f value(float u, float v, const Vector3f& p) const = 0;
	bool hasKd() const {
		return enableKd;
	}
	bool hasKs() const {
		return enableKs;
	}
	Texture* setKd(Vector3f kd) {
		this->kd = kd;
		enableKd = true;
		return this;
	}
	Texture* setKs(Vector3f ks) {
		this->ks = ks;
		enableKs = true;
		return this;
	}
	Vector3f getKd() const {
		return kd;
	}
	Vector3f getKs() const {
		return ks;
	}
private:
	bool enableKd, enableKs;
	Vector3f kd, ks;
};