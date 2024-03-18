#pragma once

#include "Vector3.h";

class Ray {

public:
	Ray() { ray_distance = 0.0f; };
	Ray(const Vector3& origin, const Vector3& direction) : ray_origin(origin), ray_direction(direction) { ray_distance = 0.0f; };
	Ray(const Vector3& origin, const Vector3& direction, float distance) : ray_origin(origin), ray_direction(direction), ray_distance(distance) {};
	Ray(const Vector3& origin, float distance) : ray_origin(origin), ray_distance(distance) {};

	Vector3 Origin() const { return ray_origin; }

	Vector3 Direction() const { return ray_direction; }

	Vector3 Destination() const { return ray_destination; }

	void setOrigin(Vector3 o) { ray_origin = o; }
	
	void setDirection(Vector3 d) { ray_direction = d; }
	
	void setDistance(Vector3 distance) { ray_direction = distance; }

	Vector3 PointAt(float t) const {
		return ray_origin + ray_direction * t;
	}

private:
	Vector3 ray_origin;
	Vector3 ray_direction;
	Vector3 ray_destination;
	float ray_distance;
};