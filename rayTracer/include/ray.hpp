#pragma once

#include "vector3.hpp"

class Ray {

public:
	Vector3 origin, direction, target;
	float length;

	Ray(const Vector3& origin, Vector3& direction, const Vector3& target = Vector3(0, 0, 0), bool directionFromTarget = false, float length = std::numeric_limits<float>::infinity());
	bool isPointOnRay(Vector3& point);
	void setDirection(Vector3& direction);
	void setTarget(Vector3& target);

	friend std::ostream& operator<<(std::ostream& os, const Ray& ray) {
		os << "Ray: " << "origin: " << ray.origin << ", direction: " << ray.direction << ", target: " << ray.target;
		return os;
	}
};