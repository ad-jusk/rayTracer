#pragma once

#include "primitive.hpp"
#include "light/lightSource.hpp"
#include "image.hpp"

class PerspectiveCamera {

private:
	Vector3 adaptiveAntialiasing(Ray& ray, Vector3& A, Vector3& B, Vector3& C, Vector3& D, Vector3& E,
		int depth, int maxDepth, Vector3 horizontal, Vector3 vertical, Vector3& backgroundColor, std::vector<Primitive*> primitives, std::vector<LightSource*> lights) const;

public:
	Vector3 position, viewDirection, up;
	int width, height, fov;

	PerspectiveCamera(const Vector3& position, const Vector3& viewDirection, int width, int height, int fov);

	void renderScene(std::vector<Primitive*> primitives, std::vector<LightSource*> lights, const bool useAntialiasing = true) const;
};