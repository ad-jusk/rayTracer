#pragma once

#include "Ray.h"

// Class representing data of ray hitting a hittable object
enum IntersectionType {
    MISS,
    HIT,
    INSIDE_PRIMITIVE
}; 
class HitRecord {
public:
    // Intersection type
    IntersectionType type;
    // Hit point
    Point3 p;
    // Hit normal
    Vector3 normal;
    // Hit interval
    double t;
};

// Class representing objects that can be hit by rays.
class Hittable {
public:
    virtual ~Hittable() = default;
    /*
        This method checks whether a ray has hit the hittable object.
        Params:
        - r - a ray to be tested for hit
        - tmin - minimum interval
        - tmax - maximum interval
        - rec - reference to HitRecord class that yields hit data
        Note: hit only counts if tmin < t < tmax.
        Returns true if ray hit the object, false otherwise.
    */
    virtual bool hit(const Ray& r, double tmin, double tmax, HitRecord& rec) const = 0;
};