#pragma once

#include "primitive.hpp"

class Sphere : public Primitive {

public:
	Vector3 center;
	float radius, area, volume;
	
	Sphere(Vector3& center, float radius, const Vector3& color = Vector3(1, 0, 0));

	virtual IntersectionInfo getRayIntersection(const Ray& ray) const;

	void changeRadius(float radius);

	friend std::ostream& operator<<(std::ostream& os, const Sphere& sphere) {
		os << "Sphere: [center = " << sphere.center << ", radius = "
			<< sphere.radius << ", area = " << sphere.area << ", volume = " << sphere.volume << "]";
		return os;
	}
};