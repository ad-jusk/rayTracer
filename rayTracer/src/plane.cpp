#include "../include/plane.hpp"

Plane::Plane(const Vector3& normal, float d, const Material& material) : Primitive(material) {
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
		return info;
	}

	float t = (this->d - (this->normalVector * ray.origin)) / (this->normalVector * ray.direction);
	
	// INTERSECTION IS BEFORE ORIGIN OF RAY
	if (t < 0) {
		return info;
	}

	float x = ray.origin.x + (t * ray.direction.x);
	float y = ray.origin.y + (t * ray.direction.y);
	float z = ray.origin.z + (t * ray.direction.z);

	Vector3 point = Vector3(x, y, z);

	float distance = ray.origin.distance(point);

	if (distance > ray.length) {
		return info;
	}

	info.hit = true;
	info.distanceFromRayOrigin = distance;
	info.point = point;
	info.hitPrimitive = this;

	return info;
}

Vector3 Plane::getNormal(const Vector3& point) const {
	return this->normalVector;
}