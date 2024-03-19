#pragma once
#include "Hittable.h"
constexpr double EPSILON = 1e-6;

class Triangle : public Hittable {

public:
	Vector3 vertices[3];
	Vector3 normals[3]; 
	
    Triangle(const Vector3& vertex1, const Vector3& vertex2, const Vector3 vertex3) {
        vertices[0] = vertex1;
        vertices[1] = vertex2;
        vertices[2] = vertex3;
    }

	Triangle(const Vector3& vertex1, const Vector3& normal1, const Vector3& vertex2, const Vector3& normal2, const Vector3 vertex3, const Vector3& normal3) {
		vertices[0] = vertex1;
		vertices[1] = vertex2;
		vertices[2] = vertex3;
		normals[0] = normal1;
		normals[1] = normal2;
		normals[2] = normal3;
	}

	virtual bool hit(const Ray& ray, double tmin, double tmax, HitRecord& rec) const override {
        // Möller–Trumbore intersection algorithm 
        Vector3 edge1 = vertices[1] - vertices[0];
        Vector3 edge2 = vertices[2] - vertices[0];
        Vector3 h = ray.Direction().cross(edge2);
        double det = dot(edge1, h);

        if (det > -EPSILON && det < EPSILON) {
            return false; // Ray is parallel to triangle
        }

        double invDet = 1.0 / det;
        Vector3 tvec = ray.Origin() - vertices[0];
        double u = invDet * dot(tvec, h);

        if (u < 0.0 || u > 1.0) {
            return false; // Intersection point is outside the triangle
        }

        Vector3 qvec = tvec.cross(edge1);
        double v = invDet * dot(ray.Direction(), qvec);

        if (v < 0.0 || u + v > 1.0) {
            return false; // Intersection point is outside the triangle
        }

        double t = invDet * dot(edge2, qvec);

        if (t < tmin || t > tmax) {
            return false; // Intersection point is outside the valid range
        }

        rec.t = t;
        rec.p = ray.Origin() + t * ray.Direction();
        rec.normal = normals[0] * (1.0 - u - v) + normals[1] * u + normals[2] * v;

        return true;
	}
};