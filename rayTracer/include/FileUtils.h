#pragma once

#include <iostream>

#include "Vector3.h"

using Color = Vector3;
float color_value = 255.999f;

void writeColorToFile(std::ostream& out, Color pixel_color) {
    out << static_cast<int>(color_value * pixel_color.get_x()) << ' '
        << static_cast<int>(color_value * pixel_color.get_y()) << ' '
        << static_cast<int>(color_value * pixel_color.get_z()) << '\n';
}