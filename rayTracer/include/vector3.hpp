#pragma once

#include <iostream>
#include <cmath>

class Vector3 {

public:
    float x, y, z;

    Vector3() : x(0), y(0), z(0) {}

    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 operator*(float scalar) const {
        return Vector3(scalar * x, scalar * y, scalar * z);
    }

    Vector3 operator/(float scalar) const {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    Vector3 operator*(const Vector3& other) const {
        return Vector3(x * other.x, y * other.y, z * other.z);
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