#include "image.hpp"

void PngImage::clearColor(const Vector3& color) {
	for (int y = 0; y < this->height; y++) {
		for (int x = 0; x < this->width; x++) {
			setPixel(y, x, color);
		}
	}
}

void PngImage::colorful6ColumnsBackground() {

	int partX = static_cast<int>(this->width / 6);
	int partY = static_cast<int>(this->height / 6);

	for (int y = 0;y < this->height;y++) {
		for (int x = 0;x < this->width;x++) {
			int column = static_cast<int>(static_cast<float>(x) / partX);
			float intensity = static_cast<float>(static_cast<float>(y) / partY / 6.0f);
			switch (column) {
			case 0: {
				setPixel(y, x, Vector3(intensity + 0.1f, 0, 0));
				break;
			}
			case 1: {
				setPixel(y, x, Vector3(0, intensity + 0.1f, 0));
				break;
			}
			case 2: {
				setPixel(y, x, Vector3(0, 0, intensity + 0.1f));
				break;
			}
			case 3: {
				setPixel(y, x, Vector3(0.7f, intensity * 0.4f, 0));
				break;
			}
			case 4: {
				setPixel(y, x, Vector3(intensity, 1, intensity * 0.4f));
				break;
			}
			case 5: {
				setPixel(y, x, Vector3(1, 1, intensity + 0.1f));
				break;
			}
			default:
				setPixel(y, x, Vector3(1, 1, intensity));
				break;
			}
		}
	}
}

void PngImage::setPixel(int y, int x, const Vector3& color) {
	size_t index = channels * width * y + channels * x;
	Vector3 clampedColor = color.clamp_0_255();
	this->imageMatrix[index] = static_cast<uint8_t>(clampedColor.x);
	this->imageMatrix[index + 1] = static_cast<uint8_t>(clampedColor.y);
	this->imageMatrix[index + 2] = static_cast<uint8_t>(clampedColor.z);
}

Vector3 PngImage::getPixelColor(int y, int x) {
	size_t index = channels * width * y + channels * x;
	float r = static_cast<float>(this->imageMatrix[index]) / 255;
	float g = static_cast<float>(this->imageMatrix[index + 1]) / 255;
	float b = static_cast<float>(this->imageMatrix[index + 2]) / 255;
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