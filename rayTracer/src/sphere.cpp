#include "sphere.hpp"

Sphere::Sphere(const Vector3& center, float radius, const Vector3& color) : Primitive(color) {
	this->center = center;
	this->changeRadius(radius);
}

void Sphere::changeRadius(float radius) {
	this->radius = radius;
	this->area = 4 * MATH_PI * (radius * radius);
	this->volume = (4 / 3) * MATH_PI * (radius * radius * radius);
}

IntersectionInfo Sphere::getRayIntersection(const Ray& ray) const  {

	IntersectionInfo info;

	Vector3 oc = ray.origin - this->center;
	float a = ray.direction * ray.direction;
	float b = 2 * (ray.direction * oc);
	float c = oc * oc - (this->radius * this->radius);
	float delta = b * b - (a * c) * 4;

	a = roundf(a * 10000) / 10000;
	b = roundf(b * 10000) / 10000;
	c = roundf(c * 10000) / 10000;
	delta = roundf(delta * 10000) / 10000;

	// NO INTERSECTION
	if (delta < 0.001f) {
		return info.miss();
	}

	// ONE INTERSECTION
	if (delta <= 0.001f && delta >= -0.001f) {
		float t = -b / (2 * a);
		// IF T IS < 0, INTERSECTION OCCURS BEFORE ORIGIN POINT OF RAY
		if (t < 0) {
			return info.miss();
		}
		info.hit = true;
		info.point = ray.origin + ray.direction * t;
		info.distanceFromRayOrigin = ray.origin.distance(info.point);
		return info;
	}

	// HERE INTERSECTION HAPPENS TWICE
	Vector3 p1;
	Vector3 p2;
	float dist1 = 0;
	float dist2 = 0;

	float t1 = (-b + sqrt(delta)) / (2 * a);

	if (t1 >= 0) {
		p1 = ray.origin + ray.direction * t1;
		dist1 = ray.origin.distance(p1);
	}

	float t2 = (-b - sqrt(delta)) / (2 * a);

	if (t2 >= 0) {
		p2 = ray.origin + ray.direction * t2;
		dist2 = ray.origin.distance(p2);
	}

	if (t1 < 0 && t2 < 0) {
		return info.miss();
	}

	if (t1 < 0) {
		info.hit = true;
		info.point = p2;
		info.distanceFromRayOrigin = dist2;
		return info;
	}

	if (t2 < 0) {
		info.hit = true;
		info.point = p1;
		info.distanceFromRayOrigin = dist1;
		return info;
	}

	// HERE WE WILL RETURN THE INTERSECTION CLOSER TO RAY ORIGIN

	info.hit = true;
	info.distanceFromRayOrigin = std::min(dist1, dist2);
	info.point = info.distanceFromRayOrigin == dist1 ? p1 : p2;

	return info;
}