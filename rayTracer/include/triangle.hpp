#pragma once

#include "primitive.hpp"

class Triangle : public Primitive {

public:
	Vector3 v1, v2, v3, normalVector;

	Triangle(Vector3& v1, Vector3& v2, Vector3& v3, const Vector3& color = Vector3(0, 0, 1));
	virtual IntersectionInfo getRayIntersection(const Ray& ray) const;

	friend std::ostream& operator<<(std::ostream& os, const Triangle& triangle) {
		os << "Triangle: vertices: " << triangle.v1 << ", " << triangle.v2 << ", " << triangle.v3;
		return os;
	}
};