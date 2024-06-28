#pragma once

#include "primitive.hpp"
#include "image.hpp"

class OrthogonalCamera {

public:
	Vector3 position, viewDirection;
	int width, height;
	float heightToWidthRatio, widthToHeightRatio;
	float xAngle, yAngle, zAngle; // ANGLES BETWEEN VIEW DIRECTION VECTOR AND X, Y, Z AXIS
	std::vector<Ray> rays;

	OrthogonalCamera(const Vector3& position, const Vector3& viewDirection, int width, int height,
		const float pixelSizeX = 0.01, const float pixelSizeY = 0.01);

	void renderScene(std::vector<Primitive*> primitives) const;
};
