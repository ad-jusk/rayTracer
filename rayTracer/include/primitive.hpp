#pragma once

#include "ray.hpp"
#include "material.hpp"

#define MATH_PI 3.14f

struct IntersectionInfo {

	bool hit = false;
	Vector3 point;
	float distanceFromRayOrigin = 0.f;
	const Primitive* hitPrimitive = nullptr;

	friend std::ostream& operator<<(std::ostream& os, const IntersectionInfo& info) {
		if (!info.hit) {
			os << "Ray did not hit primitive";
		}
		else {
			os << "Ray hit primitive -> " <<
				"intersection point: " << info.point << ", distance: " << info.distanceFromRayOrigin;
		}
		return os;
	}
};

class Primitive {

public:
	Material material;

	Primitive(const Material& material) : material(material) {}

	virtual IntersectionInfo getRayIntersection(const Ray& ray) const = 0;

	virtual Vector3 getNormal(const Vector3& point) const = 0;
};