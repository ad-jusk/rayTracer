#pragma once

#include "vector3.hpp"

class LightSource {

public:
	Vector3 color, position;
	float intensity;

	LightSource(const Vector3& position = Vector3(), const Vector3& color = Vector3(), const float intensity = 1.f)
		: position(position), color(color), intensity(intensity) {}
	
	friend std::ostream& operator<<(std::ostream& os, const LightSource& l) {
		os << "Light source: position: " << l.position << ", color: " << l.color << ", intensity: " << l.intensity;
		return os;
	}
	virtual ~LightSource() {}

	// Add a virtual function (can be a pure virtual function)
	virtual void dummyFunction() {} // This function is just to make the class polymorphic

};