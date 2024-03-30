#pragma once

#include "primitive.hpp"

class Triangle : public Primitive {

public:
	Vector3 v1, v2, v3, normalVector;

	Triangle(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Material& material);

	virtual IntersectionInfo getRayIntersection(const Ray& ray) const override;

	Vector3 getNormal(const Vector3& point) const override;

	friend std::ostream& operator<<(std::ostream& os, const Triangle& triangle) {
		os << "Triangle: vertices: " << triangle.v1 << ", " << triangle.v2 << ", " << triangle.v3;
		return os;
	}
};