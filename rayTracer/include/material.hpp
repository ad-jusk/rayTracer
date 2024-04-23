#pragma once

#include "vector3.hpp"
enum class MaterialType {
	Diffuse,
	Reflective,
	Refractive
};
class Material {

public:
	Vector3 color, ambientColor, diffuseColor, reflectColor, specularColor;
	float specularExponent, mirrorReflection, diffuseReflection;
	MaterialType materialType;
	float indexOfRefraction; 

	Material(
		const MaterialType materialType = MaterialType::Diffuse, // Default material type
		const Vector3& color = Vector3(1, 0, 0),
		// Colour of Material under white ambient light.Usually, but not always, the same as diffuseColour.
		const Vector3& ambientColor = Vector3(0.3),
		// Colour of Material under direct white light. Usually, but not always, the same as ambientColour.
		const Vector3& diffuseColor = Vector3(0.3),
		// Colour of reflected rays under direct white light. If this is zero then there are no reflections.
		const Vector3& reflectColor = Vector3(1),
		// Colour of Material's specular highlights. If this is zero then there are no highlights.
		const Vector3& specularColor = Vector3(1),
		// 'Hardness' of Material's specular hightlights or 'Shinnines' of the material - high values give small, sharp highlights.
		const float specularExponent = 2.f,
		const float mirrorReflection = 1.f,		
		const float diffuseReflection = 1.f,
		const float indexOfRefraction = 2.24f 
		) : materialType(materialType), color(color), ambientColor(ambientColor), diffuseColor(diffuseColor), specularColor(specularColor),
		specularExponent(specularExponent), mirrorReflection(mirrorReflection), diffuseReflection(diffuseReflection), indexOfRefraction(indexOfRefraction)
	{}
};