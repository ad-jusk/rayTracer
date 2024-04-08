#include "triangle.hpp"

Triangle::Triangle(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Material& material) : Primitive(material) {
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
	this->normalVector = ((v2 - v1).cross(v3 - v1)).normalize();
}

IntersectionInfo Triangle::getRayIntersection(const Ray& ray) const {

    IntersectionInfo info;

    Vector3 e1 = Vector3(this->v2.x - this->v1.x, this->v2.y - this->v1.y, this->v2.z - this->v1.z);
    Vector3 e2 = Vector3(this->v3.x - this->v1.x, this->v3.y - this->v1.y, this->v3.z - this->v1.z);
    Vector3 h = ray.direction.cross(e2);
    float a = e1 * h;

    if (a > -0.00001 && a < 0.00001) {
        return info;
    }

    float f = 1 / a;
    Vector3 s = Vector3(ray.origin.x - this->v1.x, ray.origin.y - this->v1.y, ray.origin.z - this->v1.z);
    float u = s * f * h;

    if (u < 0.0f || u > 1.0f) {
        return info;
    }

    Vector3 q = s.cross(e1);
    float v = ray.direction * f * q;

    if (v < 0.0f || u + v > 1.0f) {
        return info;
    }
    
    float distance = e2 * f * q;

    if (distance <= 0.00001) {
        return info;
    }

    info.hit = true;
    info.point = ray.origin + (ray.direction * distance);
    info.distanceFromRayOrigin = distance;
    info.hitPrimitive = this;

    return info;
}

Vector3 Triangle::getNormal(const Vector3& point) const {
    Vector3 a = this->v1 - this->v2;
    Vector3 b = this->v1 - this->v3;
    return a.cross(b);
}