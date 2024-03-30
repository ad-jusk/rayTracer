#pragma once

#include "primitive.hpp"

// PLANE EQUATION: ax + by + cz + d = 0

class Plane : public Primitive {

public:
	Vector3 normalVector;
	float a, b, c, d;

	Plane(Vector3& normal, float d, const Material& material);

	virtual IntersectionInfo getRayIntersection(const Ray& ray) const override;

	Vector3 getNormal(const Vector3& point) const override;

	friend std::ostream& operator<<(std::ostream& os, const Plane& plane) {
		os << "Plane: normal = " << plane.normalVector;
		return os;
	}
};