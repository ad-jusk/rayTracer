#include "Hittable.h"
#include "Vector3.h"

class Sphere : public Hittable {
public:
    Sphere(Point3 _center, double _radius) : center(_center), radius(_radius) {}

    bool hit(const Ray& r, double tmin, double tmax, HitRecord& rec) const override {

        Vector3 oc = r.Origin() - center;
        auto a = dot(r.Direction(), r.Direction());
        auto b = 2.0 * dot(oc, r.Direction());
        auto c = dot(oc, oc) - radius * radius;
        auto discriminant = b * b - 4 * a * c;

        if (discriminant < 0) {
            return false;
        }
        auto sqrtd = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (-b/2 - sqrtd) / a;
        if (root <= tmin || tmax <= root) {
            root = (-b/2 + sqrtd) / a;
            if (root <= tmin || tmax <= root)
                return false;
        }

        rec.t = root;
        rec.p = r.PointAt(rec.t);
        rec.normal = (rec.p - center) / radius;

        return true;
    }

private:
    Point3 center;
    double radius;
};