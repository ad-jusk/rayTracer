#pragma once

#include "vector3.hpp"
#include "Material.hpp"
#include <cstdlib>

class Ray {

private:
	//bool lightBlocked(std::vector<class Primitive*> primitives) const;
	bool lightBlocked(std::vector<class Primitive*> primitives, const Primitive* hitPrimitive, float distanceToLight) const;

public:
	Vector3 origin, direction, target;
	float length;
	const Material* medium; 

	//Ray(const Vector3& origin, const Vector3& direction, const Vector3& target = Vector3(0, 0, 0), bool directionFromTarget = false, float length = std::numeric_limits<float>::infinity());
	Ray(const Vector3& origin, const Vector3& direction, const Vector3& target = Vector3(0, 0, 0), bool directionFromTarget = false, float length = std::numeric_limits<float>::infinity(), const Material& medium = MaterialType::Diffuse);

	bool isPointOnRay(Vector3& point);
	void setDirection(Vector3& direction);
	void setTarget(Vector3& target);
	struct IntersectionInfo getPixelHit(std::vector<class Primitive*> primitives) const;
	Vector3* getPixelColor(std::vector<class Primitive*> primitives, const std::vector<class LightSource*>, int recursionNumber = 0) const;

	float getMediumRefractionIndex() const;

	friend std::ostream& operator<<(std::ostream& os, const Ray& ray) {
		os << "Ray: " << "origin: " << ray.origin << ", direction: " << ray.direction << ", target: " << ray.target;
		return os;
	}
	// Helper function to generate a random float between 0 and 1
	static float randomFloat() {
		return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	}
};