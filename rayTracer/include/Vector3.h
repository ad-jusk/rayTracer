#pragma once

#include <cmath>
#include <iostream>

class Vector3 {

public:
	float x, y, z;
	Vector3() : x(0.0f), y(0.0f), z(0.0f) {};
	Vector3(float x_val, float y_val, float z_val) : x(x_val), y(y_val), z(z_val) {}
	float get_x() const { return x; }
	float get_y() const { return y; }
	float get_z() const { return z; }
	//accessing components of Vector3 object
	float operator[](int i) const { return (i == 0) ? x : (i == 1) ? y : z; }
	//accessing / modifying components of Vector3 object
	float& operator[](int i) { return (i == 0) ? x : (i == 1) ? y : z; }

	//chaining operations on vectors
	Vector3 operator-() const { return Vector3(-x, -y, -z); }
	Vector3& operator+=(const Vector3& v) {
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}
	Vector3& operator*=(float s) {
		x *= s;
		y *= s;
		z *= s;

		return *this;
	}
	Vector3& operator/=(float s) {
		// Perform division only if s is not zero
		if (s != 0.0f) {
			return *this *= 1 / s;
		}
		else {
			std::cerr << "Error: Division by zero!" << std::endl;
			return *this;
		}
	}

	float length() const {
		return sqrt(lengthSquared());
	}

	double lengthSquared() const {
		return pow(x, 2) + pow(y, 2) + pow(z, 2);
	}
};

// POINT IS THE SAME AS VECTOR, USED FOR CLARITY
using Point3 = Vector3;

// VECTOR OPERATIONS 
inline std::ostream& operator<<(std::ostream& out, const Vector3& v) {
	return out << v.x << ' ' << v.y << ' ' << v.z;
}

inline Vector3 operator+(const Vector3& u, const Vector3& v) {
	return Vector3(u.x + v.x, u.y + v.y, u.z + v.z);
}

inline Vector3 operator-(const Vector3& u, const Vector3& v) {
	return Vector3(u.x - v.x, u.y - v.y, u.z - v.z);
}

inline Vector3 operator*(float s, const Vector3& v) {
	return Vector3(s * v.x, s * v.y, s * v.z);
}

inline Vector3 operator*(const Vector3& u, const Vector3& v) {
	return Vector3(u.x * v.x, u.y * v.y, u.z * v.z);
}

inline Vector3 operator*(const Vector3& v, float s) {
	return s * v;
}

inline Vector3 operator/(Vector3 v, float s) {
	return (1 / s) * v;
}

inline Vector3 unit_vector(Vector3 v) {
	return v / v.length();
}

inline double dot(const Vector3& u, const Vector3& v) {
	return u.x * v.x
		+ u.y * v.y
		+ u.z * v.z;
}

inline Vector3 cross(const Vector3& u, const Vector3& v) {
	return Vector3(u.y * v.z - u.z * v.y,
		u.z * v.x - u.x * v.z,
		u.x * v.y - u.y * v.x);
}