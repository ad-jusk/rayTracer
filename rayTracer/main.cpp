#include <iostream>
#include <fstream>

#include "include/FileUtils.h"
#include "include/Ray.h"
#include "include/Vector3.h"
#include "include/Camera.h"
#include "include/Sphere.h"

const double infinity = std::numeric_limits<double>::infinity();

// Returns ray color
static Color rayColor(const Ray& r) {

    Sphere sphere(Point3(0, 0, -1), 0.5);
    HitRecord record;

    if (sphere.hit(r, 0, infinity, record)) {
        return Color(1, 0, 0);
    }

    Vector3 unitDirection = unit_vector(r.Direction());
    float a = 0.5 * (unitDirection.y + 1.0);
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

int main() {

    int image_width = 400;
    auto camera_aspect_ratio = 16.0 / 9.0;
    auto focal_length = 1.0;
    auto viewport_height = 2.0;

    Vector3 camera_center = Vector3(0.3f, 0.0f, 0.0f);
    Camera camera(image_width, camera_center, viewport_height, focal_length);

    camera.CalculatImageHeight(camera_aspect_ratio);
    int image_height = camera.getImageHeight();
    camera.CalculatViewportWidth(image_height);
    camera.CalculateViewportVectors();
    camera.CalculateUpperLeftPixelLocation();

    // OUTPUT IMAGE
    std::ofstream rendered_image("../../../../image.ppm");

    // WRITE HEADER
    rendered_image << "P3\n" << image_width << " " << image_height << "\n255\n";

    // WRITE PIXEL DATA
    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {
            auto pixel_center = camera.up_l_pixel_loc + (j * camera.pixel_delta_u) + (i * camera.pixel_delta_v);
            auto ray_direction = pixel_center - camera.camera_center;
            Ray r(camera.camera_center, ray_direction);
            Color pixel_color = rayColor(r);
            writeColorToFile(rendered_image, pixel_color);
        }
    }

    rendered_image.close();

    if (rendered_image.fail()) {
        std::cerr << "Error: Failed to write to file." << std::endl;
        return 1;
    }
    else {
        std::clog << "Image rendered" << std::endl;
    }
}