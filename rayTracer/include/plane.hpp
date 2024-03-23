#pragma once

#include "primitive.hpp"

// PLANE EQUATION: ax + by + cz + d = 0

class Plane : public Primitive {

public:
	Vector3 normalVector;
	float a, b, c, d;

	Plane(Vector3& normal, float d, const Vector3& color = Vector3(0, 1, 0));

	virtual IntersectionInfo getRayIntersection(const Ray& ray) const override;

	friend std::ostream& operator<<(std::ostream& os, const Plane& plane) {
		os << "Plane: normal = " << plane.normalVector;
		return os;
	}
};