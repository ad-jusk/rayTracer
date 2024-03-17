#pragma once

#include <iostream>

#include "Vector3.h"

class Camera {
public:
    Camera(int img_width, Vector3 camera_center, double viewport_height, double focal_length);
    void CalculatImageHeight(double camera_aspect_ratio);
    void CalculatViewportWidth();
    void CalculateViewportVectors();
    void CalculateUpperLeftPixelLocation();

    auto getImageHeight() { return image_height; }
    auto getViewportHeight() { return viewport_height; }
    auto getViewportWidth() { return viewport_width; }

    Vector3 camera_center;
    Vector3 pixel_delta_u;
    Vector3 pixel_delta_v;
    Vector3 up_l_pixel;
    Vector3 up_l_pixel_loc;

private:
    int image_width;
    int image_height;
    double focal_length;
    double viewport_width;
    double viewport_height;
    // navigate the pixel grid with Vu and Vv 
    // (left to right edge vector, upper to lower edge vector)
    Vector3 viewport_u;
    Vector3 viewport_v;
};