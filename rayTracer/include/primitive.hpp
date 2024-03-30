#pragma once

#include "ray.hpp"

#define MATH_PI 3.14f

struct IntersectionInfo {

	bool hit;
	Vector3 point;
	float distanceFromRayOrigin;

	IntersectionInfo miss() {
		this->hit = false;
		this->point = Vector3(0, 0, 0);
		distanceFromRayOrigin = 0;
		return *this;
	}

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
	Vector3 color;

	Primitive(const Vector3& color) : color(color) {}

	virtual IntersectionInfo getRayIntersection(const Ray& ray) const = 0;
};