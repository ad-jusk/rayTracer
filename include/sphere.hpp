#pragma once

#include "primitive.hpp"

class Sphere : public Primitive {

public:
	Vector3 center;
	float radius, area, volume;
	
	Sphere(const Vector3& center, float radius, const Material& material);

	IntersectionInfo getRayIntersection(const Ray& ray) const override;

	Vector3 getNormal(const Vector3& point) const override;

	void changeRadius(float radius);

	friend std::ostream& operator<<(std::ostream& os, const Sphere& sphere) {
		os << "Sphere: [center = " << sphere.center << ", radius = "
			<< sphere.radius << ", area = " << sphere.area << ", volume = " << sphere.volume << "]";
		return os;
	}
};