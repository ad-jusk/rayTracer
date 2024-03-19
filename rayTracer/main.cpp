#include <iostream>
#include <fstream>

#include "include/FileUtils.h"
#include "include/Ray.h"
#include "include/Vector3.h"
#include "include/Camera.h"
#include "include/Sphere.h"
#include "include/Plane.h"
#include "include/Triangle.h"

const double infinity = std::numeric_limits<double>::infinity();
const Sphere sphere(Point3(0, 0, -1), 0.5);

void firstExercise();
void render();
Color rayColor(const Ray& r);

int main() {

    firstExercise();
    // render();
}

void firstExercise() {
    
    std::cout << "##### Exercise 1 #####" << std::endl;

    Vector3 v1(0.f, 3.f, 0.f);
    Vector3 v2(5.f, 5.f, 0.f);

    std::cout << "Sum of " << v1 << " and " << v2 << ": " << v1 + v2 << std::endl;
    std::cout << "Angle between " << v1 << " and " << v2 << ": " << v1.angle(v2) << std::endl;

    v1 = Vector3(4.f, 5.f, 1.f);
    v2 = Vector3(4.f, 1.f, 3.f);

    std::cout << "Cross product of " << v1 << " and " << v2 << ": " << v1.cross(v2) << std::endl;
    std::cout << "Normal of cross product:"  << unit_vector(v1.cross(v2)) << std::endl;

    Sphere s(Point3(0.f, 0.f, 0.f), 10);
    Vector3 rayPoint(0, 0, -20);
    Ray ray(unit_vector(rayPoint), rayPoint);
    HitRecord hitRecord;

    if (s.hit(ray, 0, infinity, hitRecord)) {
        std::cout << "Ray hit sphere in: " << hitRecord.p << std::endl;
    }
    else {
        std::cout << "Ray did not hit sphere" << std::endl;
    }

    Plane plane(Vector3(0.0f, 1.0f, 1.0f), 0.0f);
    ray = Ray(rayPoint, Vector3(0, 1, 0));

    if (plane.hit(ray, 0, infinity, hitRecord)) {
        std::cout << "Ray hit plane in: " << hitRecord.p << std::endl;
    } else {
        std::cout << "Ray did not hit plane" << std::endl;
    }

    // Triangle
    Vector3 vertexA(0, 0, 0);
    Vector3 vertexB(1, 0, 0);
    Vector3 vertexC(0, 1, 0);

    Vector3 normalA(0, 0, 1); // Normal at vertex A
    Vector3 normalB(0, 0, 1); // Normal at vertex B
    Vector3 normalC(0, 0, 1); // Normal at vertex C

    Triangle triangle(vertexA, normalA, vertexB, normalB, vertexC, normalC);
    bool result;

    std::cout << "Test triangle intersection Case 1:" << std::endl;
    ray = Ray(Vector3(-1, 0.5, 0), Vector3(1, 0.5, 0));
    result = triangle.hit(ray, 0, infinity, hitRecord);
    std::cout << "Result: " << (result ? "True" : "False") << std::endl;
    std::cout << std::endl;

    std::cout << "Test triangle intersection Case 2:" << std::endl;
    ray = Ray(Vector3(2, -1, 0), Vector3(2, 2, 0));
    result = triangle.hit(ray, 0, infinity, hitRecord);
    std::cout << "Result: " << (result ? "True" : "False") << std::endl;
    std::cout << std::endl;

    std::cout << "Test triangle intersection Case 3:" << std::endl;
    ray = Ray(Vector3(0, 0, -1), Vector3(0, 0, 1));
    result = triangle.hit(ray, 0, infinity, hitRecord);
    std::cout << "Result: " << (result ? "True" : "False") << std::endl;
    std::cout << std::endl;
}

void render() {

    int image_width = 400;
    auto camera_aspect_ratio = 16.0 / 9.0;
    auto focal_length = 1.0;
    auto viewport_height = 2.0;

    Vector3 camera_center = Vector3(0.3f, 0.0f, 0.0f);
    Camera camera(image_width, camera_center, viewport_height, focal_length);
    camera.CalculatImageHeight(camera_aspect_ratio);
    camera.CalculatViewportWidth();
    camera.CalculateViewportVectors();
    camera.CalculateUpperLeftPixelLocation();

    int image_height = camera.getImageHeight();

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
    } else {
        std::clog << "Image rendered" << std::endl;
    }
}

Color rayColor(const Ray& r) {

    HitRecord record;

    if (sphere.hit(r, 0, infinity, record)) {
        return 0.5 * (record.normal + Color(1, 1, 1));
    }

    Vector3 unitDirection = unit_vector(r.Direction());
    float a = 0.5 * (unitDirection.y + 1.0);
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}