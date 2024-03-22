#include "include/test.hpp"
#include "include/image.hpp"

int main() {

	PngImage image;
	Vector3 color(1, 0, 1);
	Vector3 secondColor(1, 0.8, 0.1);
	image.clearColor(color);

	for (int y = image.sizeY() / 2; y < image.sizeY(); y++) {
		for (int x = image.sizeX() / 2; x < image.sizeX(); x++) {
			image.setPixel(y, x, secondColor);
		}
	}

	image.save("../../../../image.png");
}