#include "../include/image.hpp"

void PngImage::clearColor(Vector3& color) {
	for (int y = 0; y < this->height; y++) {
		for (int x = 0; x < this->width; x++) {
			setPixel(y, x, color);
		}
	}
}

void PngImage::setPixel(int y, int x, Vector3& color) {
	size_t index = channels * width * y + channels * x;
	Vector3 clampedColor = color.clamp_0_255();
	this->imageMatrix[index] = static_cast<uint8_t>(clampedColor.x);
	this->imageMatrix[index + 1] = static_cast<uint8_t>(clampedColor.y);
	this->imageMatrix[index + 2] = static_cast<uint8_t>(clampedColor.z);
}

Vector3 PngImage::getPixelColor(int y, int x) {
	size_t index = channels * width * y + channels * x;
	float r = static_cast<float>(this->imageMatrix[index]);
	float g = static_cast<float>(this->imageMatrix[index] + 1);
	float b = static_cast<float>(this->imageMatrix[index] + 2);
	return Vector3(r, g, b);
}

int PngImage::len() const {
	return this->width * this->height;
}

void PngImage::save(const std::string& filename) const {
	unsigned int error = lodepng::encode(filename, this->imageMatrix, this->width, this->height, LCT_RGB);
	if (error) {
		std::cerr << "Lodepng error " << error << ": " << lodepng_error_text(error) << std::endl;
	}
	else {
		std::cout << "Image rendered" << std::endl;
	}
}