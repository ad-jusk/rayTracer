#pragma once

#include <iostream>
#include <limits>
#include <vector>
#include <cstdint>
#include <cmath>

class Vector3 {

public:
    float x, y, z;

    Vector3() : x(0), y(0), z(0) {}

    Vector3(float x) : x(x), y(x), z(x) {}

    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 operator+(float scalar) const {
        return Vector3(scalar + x, scalar + y, scalar + z);
    }

    Vector3 operator-(float scalar) const {
        return Vector3(x - scalar, y - scalar, z - scalar);
    }

    Vector3 operator*(float scalar) const {
        return Vector3(scalar * x, scalar * y, scalar * z);
    }

    Vector3 operator/(float scalar) const {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    float operator*(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 cross(const Vector3& other) const {
        return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
    }

    Vector3 normalize() const {
        return *this / length();
    }

    float length() const {
        return sqrt(x * x + y * y + z * z);
    }

    float distance(const Vector3& other) const {
        return (*this - other).length();
    }

    float angle(const Vector3& rhs) const {
        float dot = x * rhs.x + y * rhs.y + z * rhs.z;
        return acos(dot / (this->length() * rhs.length()));
    }
    float dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 clamp_0_1() const {
        float x = this->x;
        float y = this->y;
        float z = this->z;

        if (x < 0) x = 0;
        if (y < 0) y = 0;
        if (z < 0) z = 0;

        if (x > 1) x = 1;
        if (y > 1) y = 1;
        if (z > 1) z = 1;

        return Vector3(x, y, z);
    }

    Vector3 clamp_0_255() const {
        Vector3 c =  clamp_0_1();

        c.x *= 255.f;
        c.y *= 255.f;
        c.z *= 255.f;
        
        c.x = std::min(c.x, 255.f);
        c.y = std::min(c.y, 255.f);
        c.z = std::min(c.z, 255.f);
        
        return c;
    }
 
    bool operator==(const Vector3& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(const Vector3& other) const {
        return !(*this == other);
    }

    Vector3 operator-() const {
        return Vector3(-x, -y, -z);
    }

    Vector3 operator+() const {
        return Vector3(x, y, z);
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector3& vec) {
        os << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]";
        return os;
    }


};

//static Vector3 refract(const Vector3& incident, const Vector3& normal, float refractiveIndex) {
//    float cosTheta1 = -normal.dot(incident);
//    float cosTheta2Squared = 1.0f - refractiveIndex * refractiveIndex * (1.0f - cosTheta1 * cosTheta1);
//
//    // Total internal reflection
//    if (cosTheta2Squared < 0.0f) {
//        return Vector3(0.0f, 0.0f, 0.0f); // Return black (no refraction)
//    }
//
//    float cosTheta2 = sqrt(cosTheta2Squared);
//
//    return incident * refractiveIndex + normal * (refractiveIndex * cosTheta1 - cosTheta2);
//}
