#pragma once

#include "vector3.hpp"

class Material {

public:
	Vector3 color, ambientColor, diffuseColor, reflectColor, specularColor;
	float specularExponent, mirrorReflection, diffuseReflection;

	Material(
		const Vector3& color = Vector3(1, 0, 0),
		const Vector3& ambientColor = Vector3(1),
		const Vector3& diffuseColor = Vector3(1),
		const Vector3& reflectColor = Vector3(1),
		const Vector3& specularColor = Vector3(1),
		const float specularExponent = 1.f,
		const float mirrorReflection = 1.f,
		const float diffuseReflection = 1.f
		) : color(color), ambientColor(ambientColor), diffuseColor(diffuseColor), specularColor(specularColor),
		specularExponent(specularExponent), mirrorReflection(mirrorReflection), diffuseReflection(diffuseReflection)
	{}
};