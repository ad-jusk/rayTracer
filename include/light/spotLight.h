#pragma once

#include "lightSource.hpp"

class SpotLight : public LightSource {
    Vector3 direction;
    float angle; // Angle of the cone of light in radians

public:
    SpotLight(const Vector3& position = Vector3(), const Vector3& color = Vector3(), const float intensity = 1.f,
        const Vector3& direction = Vector3(0, -1, 0), const float angle = 45 * (M_PI / 180))
        : LightSource(position, color, intensity), direction(direction.normalize()), angle(angle) {}

    Vector3 getDirection(const Vector3& point) const {
        return (position - point).normalize();
    }

    float getAngle() const {
        return angle;
    }
};
