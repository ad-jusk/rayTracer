#include "camera/orthogonalCamera.hpp"

OrthogonalCamera::OrthogonalCamera(const Vector3& position, const Vector3& viewDirection, int width, int height,
	const float pixelSizeX, const float pixelSizeY) {
	this->position = position;
	this->viewDirection = viewDirection.normalize();
	this->width = width;
	this->height = height;
	this->widthToHeightRatio = static_cast<float>(width / height);
	this->heightToWidthRatio = static_cast<float>(height / width);
	this->xAngle = viewDirection.angle(Vector3(1, 0, 0));
	this->yAngle = viewDirection.angle(Vector3(0, 1, 0));
	this->zAngle = viewDirection.angle(Vector3(0, 0, 1));

	float xOffset = std::sin(this->xAngle) * pixelSizeX;
	float yOffset = std::sin(this->yAngle) * pixelSizeY;
	float zOffset = std::sin(this->zAngle) * pixelSizeX;
	Vector3 topRightCornerOffset(xOffset * width * .5f, yOffset * height * .5f, zOffset * width * .5f);
	
	for (int i = 0;i < height; i++) {
		for (int j = 0;j < width;j++) {
			Vector3 origin = this->position - topRightCornerOffset + Vector3(xOffset * i, yOffset * j, zOffset * i);
			Ray ray(origin, this->viewDirection);
			this->rays.push_back(ray);
		}
	}
}

void OrthogonalCamera::renderScene(std::vector<Primitive*> primitives) const {

	PngImage image(width, height);
	image.colorful6ColumnsBackground();

	for (int y = 0;y < this->height; y++) {
		for (int x = 0;x < this->width;x++) {
			int rayIndex = y * this->width + x;
			IntersectionInfo info = this->rays[rayIndex].getPixelHit(primitives);
			if (info.hit) {
				image.setPixel(x, y, info.hitPrimitive->material.color);
			}
		}
	}
	image.save("../../../../image_orthogonal.png");
}