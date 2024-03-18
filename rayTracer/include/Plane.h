#pragma once
#include "Vector3.h"
#include "Ray.h"
#include <cmath>
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
enum IntersectionType {
	MISS,
	HIT,
	INSIDE_PRIMITIVE
};
struct IntersectionResult {
	IntersectionType type;
	Vector3 LPOINT; // -- intersection point
	Vector3 intersectionLPOINTNormal;
	float distance;
};
class Plane
{
public:
	Vector3 normal;
	Vector3 point;
	float distance;

	Plane() : normal(Vector3()), distance(0.0f) {}
	Plane(const Vector3& normal, float distance) : normal(normal), distance(distance) {}

	bool Contains(const Vector3& point) const {
		return dot(normal, point) + distance == 0.0f;
	}

	// This is a function to find intersection for 3 planes, might be usable later
	static bool Intersect3(const Plane& p1, const Plane& p2, const Plane& p3, Vector3& result) {
		
		//find LPOINT of intersection of 3 Planes
		float denominator = dot(p1.normal, cross(p2.normal, p3.normal));
		if (denominator == 0.0f) {
			std::cout << "INTERSECTION DIDN'T HAPPEN" << std::endl;
			return false; // No intersection
		}
		Vector3 temp1 = cross(p2.normal, p3.normal) * p1.distance;
		Vector3 temp2 = cross(p3.normal, p1.normal) * p2.distance;
		Vector3 temp3 = cross(p1.normal, p2.normal) * p3.distance;

		result = (temp1 + temp2 + temp3) / (-denominator);
		std::cout << "Intersection Point: " << result << std::endl;
		std::cout << "INTERSECTION HAPPENED" << std::endl;

		return true;
	}
	
	// Finds intersection of plane and ray
	IntersectionResult Intersects(const Ray& ray, float range) const;

	//Plane AddTiltedPlane(float angle_degrees, float distance_from_origin) {
	//	// plane titled 45 degress on Y Z axis
	//	float angle_radians = angle_degrees * M_PI / 180.0f;
	//	float normal_component = std::cos(angle_radians) * std::sqrt(2.0f) / 2.0f;
	//	Vector3 plane_normal(0.0f, normal_component, normal_component);
	//	return Plane(plane_normal, distance_from_origin);
	//}
};
