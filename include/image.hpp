#pragma once

#include "lodepng.h"
#include "vector3.hpp"

class PngImage {

private:
	int width, height, channels;
	std::vector<uint8_t> imageMatrix;

public:
	PngImage(const int width = 500, const int height = 500, const int channels = 3) : width(width), height(height), channels(channels) {
		this->imageMatrix.resize(width * height * channels, 255);
	}

	void clearColor(const Vector3& color);

	void colorful6ColumnsBackground();

	void setPixel(int y, int x, const Vector3& color);

	Vector3 getPixelColor(int y, int x);

	int len() const;

	int sizeX() const { return width; }

	int sizeY() const { return height; }

	void save(const std::string& filename) const;
};