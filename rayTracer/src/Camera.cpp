#include "../include/Camera.h"

Camera::Camera(int img_width, Vector3 camera_center, double viewport_height, double focal_length)
	: image_width(img_width), camera_center(camera_center), viewport_height(viewport_height), focal_length(focal_length) {
	image_height = 0;
	viewport_width = 0.0;
}

void Camera::CalculatImageHeight(double camera_aspect_ratio) {
	image_height = static_cast<int>(image_width / camera_aspect_ratio);
	// ensure that image_height is at least 1.
	image_height = (image_height < 1) ? 1 : image_height;
}

void Camera::CalculatViewportWidth(int img_height) {
	viewport_width = viewport_height * (static_cast<double>(image_width) / img_height);
}

void Camera::CalculateViewportVectors() {
	viewport_u = Vector3(viewport_width, 0, 0);
	viewport_v = Vector3(0, -viewport_height, 0);
	pixel_delta_u = viewport_u / image_width;
	pixel_delta_v = viewport_v / image_height;
}

void Camera::CalculateUpperLeftPixelLocation() {
	up_l_pixel = camera_center - Vector3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
	up_l_pixel_loc = up_l_pixel + 0.5 * (pixel_delta_u + pixel_delta_v);
}
