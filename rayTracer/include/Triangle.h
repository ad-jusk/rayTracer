#include "Hittable.h"
#include "Vector3.h"
constexpr double EPSILON = 1e-6; 

class Triangle : public Hittable
{
public:
	Vector3 vertices[3];
	Vector3 normals[3]; 
	
	Triangle();

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
        double a = dot(edge1, h);

        if (a > -EPSILON && a < EPSILON) {
            return false; // Ray is parallel to triangle
        }

        double f = 1.0 / a;
        Vector3 s = ray.Origin() - vertices[0];
        double u = f * dot(s, h);

        if (u < 0.0 || u > 1.0) {
            return false; // Intersection point is outside the triangle
        }

        Vector3 q = s.cross(edge1);
        double v = f * dot(ray.Direction(), q);

        if (v < 0.0 || u + v > 1.0) {
            return false; // Intersection point is outside the triangle
        }

        double t = f * dot(edge2, q);

        if (t < tmin || t > tmax) {
            return false; // Intersection point is outside the valid range
        }

        rec.t = t;
        rec.p = ray.PointAt(t);
        rec.normal = normals[0] * (1.0 - u - v) + normals[1] * u + normals[2] * v;

        return true;
//		Vector3 AB = vertices[1] - vertices[0];
//		Vector3 AC = vertices[2] - vertices[0];
//		Vector3 normal = AB.cross(AC);
//
//		float _dot = dot(normal, ray.Direction());
//		if (fabsf(_dot) < EPSILON){
//			return false;
//		}
//
//		float t = dot(normal, vertices[0] - ray.Origin()) / _dot;
//
//		if (t < 0.0f) {
//			return false;
//		}
//
//		rec.p = ray.Origin() + ray.Direction() * t;
//
//		Vector3 AP = rec.p - vertices[0];
//		Vector3 BP = rec.p - vertices[1];
//		Vector3 CP = rec.p - vertices[2];
//		Vector3 v1 = AB.cross(AP);
//		Vector3 v2 = AC.cross(BP);
//		Vector3 v3 = (vertices[1] - vertices[2]).cross(CP);
//
//		if (dot(v1, normal) >= 0.0f && dot(v2, normal) >= 0.0f && dot(v3, normal) >= 0.0f)
//		{
//			return true;
//		}
//		return false;
	}
};