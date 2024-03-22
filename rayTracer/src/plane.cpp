#include "../include/plane.hpp"

Plane::Plane(Vector3& normal, float d, const Vector3& color) : Primitive(color) {
	this->normalVector = normal;
	this->a = normal.x;
	this->b = normal.y;
	this->c = normal.z;
	this->d = d;
}

IntersectionInfo Plane::getRayIntersection(const Ray& ray) const {

	IntersectionInfo info;

	// RAY IS PARALLEL
	if (this->normalVector * ray.direction == 0) {
		return info.miss();
	}

	float t = (this->d - (this->normalVector * ray.origin)) / (this->normalVector * ray.direction);
	
	// INTERSECTION IS BEFORE ORIGIN OF RAY
	if (t < 0) {
		return info.miss();
	}

	float x = ray.origin.x + (t * ray.direction.x);
	float y = ray.origin.y + (t * ray.direction.y);
	float z = ray.origin.z + (t * ray.direction.z);

	Vector3 point = Vector3(x, y, z);

	float distance = ray.origin.distance(point);

	if (distance > ray.length) {
		return info.miss();
	}

	info.hit = true;
	info.distanceFromRayOrigin = distance;
	info.point = point;

	return info;
}