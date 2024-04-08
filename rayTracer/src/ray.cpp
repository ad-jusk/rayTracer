#include "primitive.hpp"
#include "light/lightSource.hpp"
#include <algorithm>

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

Vector3 reflect(const Vector3& incident, const Vector3& normal) {
    return incident - normal * 2 * incident.dot(normal);
}

//Phong Reflection Model Equation :
/*
     I = k_a * I_a + k_d * (N ⋅ L) * I_d + k_s * (R ⋅ V)^n * I_s

     Where:
     I   : Intensity of the pixel.
     I_a : Intensity of the ambient light.
     I_d : Intensity of the diffuse light.
     I_s : Intensity of the specular light.
     (they are all equal to intensity of the light source we have done for this raytracer)

     k_a : Ambient reflection coefficient.
     k_d : Diffuse reflection coefficient.
     k_s : Specular reflection coefficient.

     N   : Normal vector at the point of intersection.
     L   : Unit vector in the direction of the light source.
     R   : Reflection vector.
     V   : Unit vector towards the viewer.

     n   : Shininess factor, representing the specular exponent.
*/
Vector3* Ray::getPixelColor(std::vector<Primitive*> primitives, const std::vector<LightSource*> lights) const {

    IntersectionInfo info = this->getPixelHit(primitives);

    float ambientIntensity = 0.2f;
    Vector3 ambientColor(ambientIntensity, ambientIntensity, ambientIntensity);

    if (!info.hit) {
        return nullptr;
    }

    float r = ambientColor.x;
    float g = ambientColor.y;
    float b = ambientColor.z;

    for (LightSource* l : lights) {
        const float distance = info.point.distance(l->position);
        Vector3 lightDirection = (l->position - info.point).normalize();

        // Create shadow ray towards the light source
        Ray shadowRay(info.point, lightDirection, Vector3(), false, distance);

        if (!shadowRay.lightBlocked(primitives, info.hitPrimitive, distance)) {
            Vector3 normal = info.hitPrimitive->getNormal(info.point).normalize();
            Vector3 viewDirection = (this->origin - info.point).normalize();
            Vector3 reflectionDirection = reflect(-lightDirection, normal).normalize();

            // Diffuse shading
            // Diffuse Reflection : I_l * k_d * (N.L)

            float diffuseFactor = std::max(0.0f, lightDirection.dot(normal));
            Vector3 diffuseColor = info.hitPrimitive->material.diffuseColor * diffuseFactor;

            // Specular shading
            // Specular Reflection : I_l * k_s * (R.V) ^ n

            float specularFactor = std::pow(std::max(0.0f, viewDirection.dot(reflectionDirection)), info.hitPrimitive->material.specularExponent);
            Vector3 specularColor = info.hitPrimitive->material.specularColor * specularFactor;

            /* 
             final_color = ambient_color + diffuse_color + specular_color 
             ( ambient_color is realtively r,g,b since they are equal to ambient_color x,y,z )
             l->intensity is the I_l we didnt multiply the colors by before

             The attenuation factor, 1 / (distance ^ 2), represents the inverse square law
             of light attenuation with distance, although it's not explicitly part of the Phong equation.
             It's used to attenuate the intensity of the light based on the distance between the light source and the surface point.  
            */
            r += (diffuseColor.x + specularColor.x) * l->intensity / (distance * distance);
            g += (diffuseColor.y + specularColor.y) * l->intensity / (distance * distance);
            b += (diffuseColor.z + specularColor.z) * l->intensity / (distance * distance);
        }
    }

    r *= info.hitPrimitive->material.color.x;
    g *= info.hitPrimitive->material.color.y;
    b *= info.hitPrimitive->material.color.z;

    Vector3* finalColor = new Vector3(r, g, b);
    *finalColor = finalColor->clamp_0_1();

    return finalColor;
}

bool Ray::lightBlocked(std::vector<class Primitive*> primitives, const Primitive* hitPrimitive, float distanceToLight) const {
    for (Primitive* p : primitives) {
        if (p == hitPrimitive) continue; // Skip the object that was hit
        IntersectionInfo info = p->getRayIntersection(*this);
        if (info.hit && info.distanceFromRayOrigin < distanceToLight) {
            return true;
        }
    }
    return false;
}
