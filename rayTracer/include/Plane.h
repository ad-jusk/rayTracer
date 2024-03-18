#pragma once

#include <cmath>

#include "Vector3.h"
#include "Hittable.h"
#include "Ray.h"

#define M_PI 3.14159265358979323846
/*
	plane equation 
	n ⋅ (p − p0) = 0

	p = o + td
		 p(t) -> point that lies on the ray
		 o -> origin of the ray
		 d -> direction of the ray
	 | 
	 v	 
	n ⋅ (o + d ⋅ t − p0) = 0

	równanie parametrycznego promienia:
	t = − ((o − p0) ⋅ n)/(l ⋅ n) = ((p0 − o) ⋅ n)/(l ⋅ n)
*/

class Plane : public Hittable {

public:
    Plane() : normal(Vector3()), distance(0.0f) {}
    Plane(const Vector3& normal, float distance) : normal(normal), distance(distance) {}

	virtual bool hit(const Ray& ray, double tmin, double tmax, HitRecord& rec) const override {
		double ndotD = dot(normal, ray.Direction());
		rec.type = MISS;

		if (ndotD == 0) {
			return false; // Ray is parallel to the plane
		}

		double t = (-distance - dot(normal, ray.Origin())) / ndotD;

		if (t < tmin || t > tmax) {
			return false; // t is outside the valid range
		}
		else {
			if (dot(normal, ray.Direction()) < 0)
				rec.type = HIT;
			else
				rec.type = INSIDE_PRIMITIVE;
			rec.t = t;
			rec.p = ray.Origin() + t * ray.Direction();
			rec.normal = normal;
		}
		return true;
	};

private:
	Vector3 normal;
	float distance;
};