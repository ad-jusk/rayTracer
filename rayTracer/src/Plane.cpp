#include "Plane.h"

IntersectionResult Plane::Intersects(const Ray& ray, float range) const {
	IntersectionResult result;
	result.type = MISS;

	float ndotD = dot(normal, ray.Direction());

	if (ndotD == 0) {
		return result;
	}

	// równanie parametrycznego promienia :
	// t = −((o − p0) ⋅ n) / (l ⋅ n) = ((p0 − o) ⋅ n) / (l ⋅ n)

	float t = (-distance - dot(normal, ray.Origin())) / ndotD;

	float denominator = dot(normal, ray.Direction());

	if (t > 0) {
		if (range == 0.0f || t < range) {
			if (dot(normal, ray.Direction()) < 0)
				result.type = HIT;
			else
				result.type = INSIDE_PRIMITIVE;

			result.LPOINT = ray.Origin() + t * ray.Direction();
			result.distance = t;
			result.intersectionLPOINTNormal = normal;
		}
	}

	return result;
}
