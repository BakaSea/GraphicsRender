#include "Triangle.h"
#include <iostream>
using namespace std;

Triangle::Triangle(const Vector3f& v0, const Vector3f& v1, const Vector3f& v2, Material* material)
	: v0(v0), v1(v1), v2(v2), material(material) {
	e0 = v1 - v0;
	e1 = v2 - v0;
	normal = normalize(cross(e0, e1));
	vt0 = Vector2f(0, 0);
	vt1 = Vector2f(1, 0);
	vt2 = Vector2f(0, 1);
	useVn = false;
}

Triangle::Triangle(const Vector3f& v0, const Vector3f& v1, const Vector3f& v2, 
	const Vector2f& vt0, const Vector2f& vt1, const Vector2f& vt2, Material* material)
	: Triangle(v0, v1, v2, material) {
	this->vt0 = vt0;
	this->vt1 = vt1;
	this->vt2 = vt2;
}

void Triangle::setVertexNormal(const Vector3f& vn0, const Vector3f& vn1, const Vector3f& vn2) {
	this->vn0 = vn0;
	this->vn1 = vn1;
	this->vn2 = vn2;
	this->useVn = true;
}

bool Triangle::hit(const Ray3f& ray, float tMin, float tMax, HitRecord& record) const {
	Vector3f T = ray.origin() - v0;
	Vector3f Q = cross(T, e0);
	Vector3f P = cross(ray.direction(), e1);
	float PE0 = dot(P, e0);
	float QE1 = dot(Q, e1);
	float PT = dot(P, T);
	float QD = dot(Q, ray.direction());
	float t = QE1 / PE0;
	float u = PT / PE0;
	float v = QD / PE0;
	record.t = t;
	Vector2f uv = (1 - u - v) * vt0 + u * vt1 + v * vt2;
	record.u = uv.x();
	record.v = uv.y();
	record.p = ray.point(t);
	if (useVn) {
		record.normal = (1 - u - v) * vn0 + u * vn1 + v * vn2;
	} else {
		record.normal = normal;
	}
	record.material = material;
	if (u + v <= 1 && u >= 0 && v >= 0 && tMin < t && t < tMax) {
		return true;
	} else return false;
}

bool Triangle::getBoundingBox(float t0, float t1, AABB& box) const {
	box = AABB(Vector3f(ffmin(v0.x(), ffmin(v1.x(), v2.x())),
		ffmin(v0.y(), ffmin(v1.y(), v2.y())),
		ffmin(v0.z(), ffmin(v1.z(), v2.z()))),
		Vector3f(ffmax(v0.x(), ffmax(v1.x(), v2.x())),
			ffmax(v0.y(), ffmax(v1.y(), v2.y())),
			ffmax(v0.z(), ffmax(v1.z(), v2.z()))));
	return true;
}

float Triangle::pdfValue(const Ray3f& ray) const {
	HitRecord record;
	if (hit(ray, 0.001f, FLT_MAX, record)) {
		float area = cross(e0, e1).length() / 2.0f;
		float disSquared = record.t * record.t;
		float cosine = fabs(dot(ray.direction(), record.normal));
		return disSquared / (cosine * area);
	} else return 0.0f;
}

Vector3f Triangle::random(const Vector3f& origin, Sampler& sampler) const {
	Vector2f uv = sampler.generate2D([](Vector2f point) -> Vector2f {
		float sqrtU = sqrt(point.x());
		return Vector2f(1 - sqrtU, sqrtU * point.y());
	});
	Vector3f point = v0 + uv.x() * e0 + uv.y() * e1;
	return point - origin;
}

float Triangle::pdfWeight() const {
	return cross(e0, e1).length() / 2.0f;
}
