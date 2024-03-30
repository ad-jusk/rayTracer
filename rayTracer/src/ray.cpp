#include "primitive.hpp"
#include "light/lightSource.hpp"

Ray::Ray(const Vector3& origin, const Vector3& direction, const Vector3& target, bool directionFromTarget, float length) {

	this->origin = origin;
	this->length = length;

	if (directionFromTarget) {
		// CALCULATE DIRECTION FROM TARGET
		if (target == origin) {
			throw std::invalid_argument("Ray cannot have equal origin and target");
		}
		this->target = target;
		this->direction = this->origin - target;
		this->direction = this->direction.normalize();
	}
	else {
		// CALCULATE TARGET FROM DIRECTION
		if (direction == Vector3()) {
			throw std::invalid_argument("Ray direction vector cannot be (0, 0, 0)");
		}
		this->direction = direction.normalize();
		this->target = this->origin + this->direction;
	}
}

bool Ray::isPointOnRay(Vector3& point) {

    bool skip_x = false, skip_y = false, skip_z = false;

    if (direction.x == 0) {
        if (point.x != origin.x) {
            return false;
        }
        skip_x = true;
    }
    if (direction.y == 0) {
        if (point.y != origin.y) {
            return false;
        }
        skip_y = true;
    }
    if (direction.z == 0) {
        if (point.z != origin.z) {
            return false;
        }
        skip_z = true;
    }

    double x_var, y_var, z_var;

    if (!skip_x) {
        x_var = std::round((point.x - origin.x) / direction.x);
    }
    if (!skip_y) {
        y_var = std::round((point.y - origin.y) / direction.y);
    }
    if (!skip_z) {
        z_var = std::round((point.z - origin.z) / direction.z);
    }

    if (!((skip_x || skip_y || x_var == y_var) && (skip_y || skip_z || y_var == z_var) && (skip_x || skip_z || x_var == z_var))) {
        return false;
    }

    if ((!skip_x && x_var < 0) || (!skip_y && y_var < 0) || (!skip_z && z_var < 0)) {
        return false;
    }

    if (origin.distance(point) > length) {
        return false;
    }

    return true;
}

void Ray::setDirection(Vector3& direction) {
    if (direction == Vector3()) {
        throw std::invalid_argument("Ray direction vector cannot be (0, 0, 0)");
    }
    this->direction = direction.normalize();
    this->target = this->origin + direction;
}

void Ray::setTarget(Vector3& target) {
    if (target == this->origin) {
        throw std::invalid_argument("Ray cannot have equal origin and target");
    }
    this->target = target;
    this->direction = (this->target - this->origin).normalize();
}

IntersectionInfo Ray::getPixelHit(std::vector<Primitive*> primitives) const {

    float distance = std::numeric_limits<float>::max();
    IntersectionInfo closest;

    for (Primitive* p : primitives) {
        IntersectionInfo info = p->getRayIntersection(*this);
        if (info.hit && info.distanceFromRayOrigin < distance) {
            closest = info;
            distance = info.distanceFromRayOrigin;
        }
    }
    return closest;
}

Vector3* Ray::getPixelColor(std::vector<Primitive*> primitives, const std::vector<LightSource*> lights) const {

    IntersectionInfo info = this->getPixelHit(primitives);

    float r, g, b;
    
    // AMBIENT LIGHT
    r = g = b = 0.2f;

    if (!info.hit) {
        return nullptr;
    }

    for (LightSource* l : lights) {

        const float distance = info.point.distance(l->position);
        Ray ray = Ray(info.point, Vector3(), l->position, true);

        if (ray.lightBlocked(primitives)) {
            continue;
        }

        Vector3 normal = info.hitPrimitive->getNormal(info.point).normalize();
        Vector3 direction = ray.direction.normalize();
        float fallof = std::fabs(normal * direction / (normal.length() * direction.length()));
        
        float i = l->intensity * fallof / (distance * distance);
        i = std::min(i, 1.f);

        Vector3 reflection = -ray.direction - normal * (-ray.direction * normal) * 2;
        float intensity = -i * std::pow(info.hitPrimitive->material.mirrorReflection * (direction * normal) + info.hitPrimitive->material.diffuseReflection * (reflection * -this->direction), info.hitPrimitive->material.specularExponent);
        intensity = std::min(intensity, 1.f);

        r += l->color.x * intensity;
        g += l->color.y * intensity;
        b += l->color.z * intensity;
    }

    float final_r = info.hitPrimitive->material.color.x * r;
    float final_g = info.hitPrimitive->material.color.y * g;
    float final_b = info.hitPrimitive->material.color.z * b;
    
    return new Vector3(final_r, final_g, final_b);
}

bool Ray::lightBlocked(std::vector<class Primitive*> primitives) const {
    // TODO: THIS HAS TO RETURN FALSE IF ONE PRIMITIVE 
    // IS SHADOWED BY ANOTHER
    for (Primitive* p : primitives) {
        IntersectionInfo info = p->getRayIntersection(*this);
        if (info.hit) {
            return false;
        }
    }
    return true;
}