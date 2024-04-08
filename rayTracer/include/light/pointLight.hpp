#pragma once

#include "lightSource.hpp"

class PointLight : public LightSource {

public:
	PointLight(const Vector3& position = Vector3(), const Vector3& color = Vector3(), const float intensity = 1.f)
	: LightSource(position, color, intensity)  {}
};