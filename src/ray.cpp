#include "primitive.hpp"
#include "light/lightSource.hpp"


Ray::Ray(const Vector3& origin, const Vector3& direction, const Vector3& target, bool directionFromTarget, float length, const Material& medium) {
    
    this->origin = origin;
    this->length = length;
    this->medium = &medium;

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

// Calculate Fresnel effect
float fresnel(const Vector3& incident, const Vector3& normal, float etai, float etat) {
    float cosi = -std::clamp(incident.dot(normal), -1.0f, 1.0f);
    float sint2 = etai * etai * (1.0f - cosi * cosi) / (etat * etat);
    if (sint2 > 1.0f) {
        // Total internal reflection
        return 1.0f;
    }
    float cost = sqrtf(1.0f - sint2);
    float r0 = (etat - etai) / (etat + etai);
    r0 = r0 * r0;
    return r0 + (1.0f - r0) * powf(1.0f - cosi, 5.0f);
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
Vector3* Ray::getPixelColor(std::vector<Primitive*> primitives, const std::vector<LightSource*> lights, int recursionNumber) const {
    const int recursionLimit = 6;


    IntersectionInfo info = this->getPixelHit(primitives);

    float ambientIntensity = 0.3f;
    Vector3 ambientColor(ambientIntensity, ambientIntensity, ambientIntensity);

    if (!info.hit) {
        return nullptr;
    }

    float r = info.hitPrimitive->material.ambientColor.x;
    float g = info.hitPrimitive->material.ambientColor.y;
    float b = info.hitPrimitive->material.ambientColor.z;


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
    r = r * info.hitPrimitive->material.color.x;
    g = g * info.hitPrimitive->material.color.y;
    b = b * info.hitPrimitive->material.color.z;

    // Reflection
    if (info.hitPrimitive->material.materialType == MaterialType::Reflective && recursionNumber < recursionLimit) {
        Vector3 reflectionDirection = reflect(this->direction, info.hitPrimitive->getNormal(info.point)).normalize();
        // Offset the origin to avoid self-intersection
        Ray reflectedRay(info.point + reflectionDirection * 1e-4, reflectionDirection, Vector3(), false, std::numeric_limits<float>::max(), info.hitPrimitive->material);
        Vector3* reflectedColor = reflectedRay.getPixelColor(primitives, lights, recursionNumber + 1);
        
        if (reflectedColor != nullptr) {
            r += (*reflectedColor).x;
            g += (*reflectedColor).y;
            b += (*reflectedColor).z;
            delete reflectedColor;
        }
    }

    // Refraction
    if (info.hitPrimitive->material.materialType == MaterialType::Refractive && recursionNumber < recursionLimit) {
        float eta = this->getMediumRefractionIndex(); // Index of refraction of the material
        Vector3 normal = info.hitPrimitive->getNormal(info.point).normalize();
        Vector3 incident = this->direction.normalize();

        // Ensure eta is valid
        if (eta <= 0.0f) {
            std::cerr << "Invalid index of refraction." << std::endl;
            return nullptr;
        }

        float cosi = std::max(-1.0f, std::min(1.0f, incident.dot(normal)));
        float etai = 1.0f;
        float etat = eta;
        Vector3 n = normal;

        if (cosi < 0.0f) {
            cosi = -cosi;
        }
        else {
            std::swap(etai, etat);
            n = -normal;
        }

        float etaRatio = etai / etat;
        float k = 1.0f - etaRatio * etaRatio * (1.0f - cosi * cosi);

        if (k >= 0.0f) {
            Vector3 refractedDirection = incident * etaRatio +n * (etaRatio * cosi - sqrtf(k));
            refractedDirection.normalize();

            Vector3 refractedOrigin = info.point + refractedDirection * 1e-4;

            Ray refractedRay(refractedOrigin, refractedDirection * 1e-4, Vector3(), false, std::numeric_limits<float>::max(), info.hitPrimitive->material);
            Vector3* refractedColor = refractedRay.getPixelColor(primitives, lights, recursionNumber + 1);
            if (refractedColor != nullptr) {
                r += (*refractedColor).x;
                g += (*refractedColor).y;
                b += (*refractedColor).z;
                delete refractedColor;
            }
        }
        else {
            // Total internal reflection
            Vector3 reflectionDirection = reflect(incident, normal);
            Vector3 refractedOrigin = info.point + reflectionDirection * 1e-4;
            Ray reflectedRay(refractedOrigin, reflectionDirection * 1e-4, Vector3(), false, std::numeric_limits<float>::max(), info.hitPrimitive->material);
            Vector3* reflectedColor = reflectedRay.getPixelColor(primitives, lights, recursionNumber + 1);
            if (reflectedColor != nullptr) {
                r += (*reflectedColor).x;
                g += (*reflectedColor).y;
                b += (*reflectedColor).z;
                delete reflectedColor;
            }
        }
    }
    Vector3* finalColor = new Vector3(r, g, b);
    *finalColor = finalColor->clamp_0_1();
    
    return finalColor;
}

float Ray::getMediumRefractionIndex() const {
    if (medium == nullptr) {
        return 1.0f; // Air or vacuum
    }
    else {
        return medium->indexOfRefraction;
    }
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
