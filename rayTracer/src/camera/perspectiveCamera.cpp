#include "camera/perspectiveCamera.hpp"

PerspectiveCamera::PerspectiveCamera(const Vector3& position, const Vector3& viewDirection, int width, int height, int fov) {
	this->position = position;
	this->viewDirection = viewDirection.normalize();
	this->width = width;
	this->height = height;
	this->fov = fov;
	this->up = Vector3(0, 1, 0);
}

//			A-------B
//			|		|
// PIXEL ->	|   E	|
//			|		|
//			D-------C
Vector3 PerspectiveCamera::adaptiveAntialiasing(Ray& ray, Vector3& A, Vector3& B, Vector3& C, Vector3& D, Vector3& E,
	int depth, int maxDepth, Vector3 horizontal, Vector3 vertical,
	Vector3& backgroundColor, std::vector<Primitive*> primitives) const {

	Vector3 colorA, colorB, colorC, colorD, colorE, zeroVector;
	colorA = colorB = colorC = colorD = colorE = backgroundColor;

	if (E != zeroVector) {
		ray.setTarget(E);
		Vector3* color = ray.getPixelColor(primitives);
		if (color) {
			colorE = *color;
		}
	}
	else {
		colorE = E;
	}

	if (depth > maxDepth) return colorE;

	if (A != zeroVector) {
		ray.setTarget(A);
		Vector3* color = ray.getPixelColor(primitives);
		if (color) {
			colorA = *color;
		}
	}
	else {
		colorA = A;
	}

	if (B != zeroVector) {
		ray.setTarget(B);
		Vector3* color = ray.getPixelColor(primitives);
		if (color) {
			colorB = *color;
		}
	}
	else {
		colorB = B;
	}

	if (C != zeroVector) {
		ray.setTarget(C);
		Vector3* color = ray.getPixelColor(primitives);
		if (color) {
			colorC = *color;
		}
	}
	else {
		colorC = C;
	}

	if (D != zeroVector) {
		ray.setTarget(D);
		Vector3* color = ray.getPixelColor(primitives);
		if (color) {
			colorD = *color;
		}
	}
	else {
		colorD = D;
	}

	if (colorA != colorE) {
		Vector3 primB = E + vertical;
		Vector3 primD = E - horizontal;
		Vector3 primE = E - horizontal / 2 + vertical / 2;
		colorA = adaptiveAntialiasing(ray, colorA, primB, colorE, primD, primE, depth + 1, maxDepth, horizontal / 2, vertical / 2, backgroundColor, primitives);
	}

	if (colorB != colorE) {
		Vector3 primA = E + vertical;
		Vector3 primC = E + horizontal;
		Vector3 primE = E + horizontal / 2 + vertical / 2;
		colorB = adaptiveAntialiasing(ray, primA, colorB, primC, colorE, primE, depth + 1, maxDepth, horizontal / 2, vertical / 2, backgroundColor, primitives);
	}

	if (colorC != colorE) {
		Vector3 primB = E + horizontal;
		Vector3 primD = E - vertical;
		Vector3 primE = E + horizontal / 2 - vertical / 2;
		colorC = adaptiveAntialiasing(ray, colorE, primB, colorC, primD, primE, depth + 1, maxDepth, horizontal / 2, vertical / 2, backgroundColor, primitives);
	}

	if (colorD != colorE) {
		Vector3 primA = E - horizontal;
		Vector3 primC = E - vertical;
		Vector3 primE = E - horizontal / 2 - vertical / 2;
		colorD = adaptiveAntialiasing(ray, primA, colorE, primC, colorD, primE, depth + 1, maxDepth, horizontal / 2, vertical / 2, backgroundColor, primitives);
	}

	Vector3 AE = (colorA + colorE) * .5f;
	Vector3 BE = (colorB + colorE) * .5f;
	Vector3 CE = (colorC + colorE) * .5f;
	Vector3 DE = (colorD + colorE) * .5f;
	Vector3 sum = AE + BE + CE + DE;

	return sum * .25f;
}

void PerspectiveCamera::renderScene(std::vector<Primitive*> primitives, const bool useAntialiasing) const {

	PngImage image(this->width, this->height);
	image.colorful6ColumnsBackground();

	float theta = static_cast<float>(this->fov * MATH_PI / 180);
	float halfHeight = std::tan(theta / 2.0f);
	float aspect = static_cast<float>(this->width / this->height);
	float halfWidth = aspect * halfHeight;
	float nearPlane = (this->viewDirection - this->position).length();

	Vector3 w = (-this->position - this->viewDirection).normalize();
	Vector3 u = (-(this->up.cross(w))).normalize();
	Vector3 v = w.cross(u).normalize();

	float u0 = this->position.x - halfWidth * nearPlane;
	float v0 = this->position.y - halfHeight * nearPlane;

	Vector3 lowerLeftCorner = u * u0 + v * v0 - w * nearPlane;
	Vector3 horizontal = u * (2 * halfWidth * nearPlane);
	Vector3 vertical = v * (2 * halfWidth * nearPlane);
	Vector3 pixelX = horizontal / static_cast<float>(this->width);
	Vector3 pixelY = vertical / static_cast<float>(this->height);

	Vector3 rayTarget;

	for (int y = 0;y < this->height;y++) {
		for (int x = 0;x < this->width;x++) {

			rayTarget = lowerLeftCorner + pixelY * static_cast<float>(y) + pixelX * static_cast<float>(x) + pixelX / 2 + pixelY / 2;

			if (useAntialiasing) {
				Vector3 cornerA = rayTarget - pixelX / 2 + pixelY / 2;
				Vector3 cornerB = rayTarget + pixelX / 2 + pixelY / 2;
				Vector3 cornerC = rayTarget + pixelX / 2 - pixelY / 2;
				Vector3 cornerD = rayTarget - pixelX / 2 - pixelY / 2;
				Vector3 direction;
				Ray ray = Ray(this->position, direction, rayTarget, true);
				Vector3 bgColor = image.getPixelColor(y, x);
				Vector3 color = adaptiveAntialiasing(ray, cornerA, cornerB, cornerC, cornerD, rayTarget, 0, 5, pixelX / 2, pixelY / 2, bgColor, primitives);
				image.setPixel(y, x, color);
			}
			else {
				Vector3 direction;
				Ray ray = Ray(this->position, direction, -rayTarget, true);
				Vector3* color = ray.getPixelColor(primitives);
				if (color) {
					image.setPixel(y, x, *color);
				}
			}
		}
	}
	image.save("../../../../image_perspective.png");
}