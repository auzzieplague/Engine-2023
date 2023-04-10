#pragma once

#include <glm/vec3.hpp>
#include <glm/glm.hpp>

/**
 * @author Michael.Whinfrey
 */
class BoundingSphere {
    glm::vec3 center;
    float radius;

    BoundingSphere(const glm::vec3 &center, float radius) : center(center), radius(radius) {};
public:
    BoundingSphere() : center(0.0f), radius(0.0f) {}

    [[nodiscard]] bool isCollidingWith(const BoundingSphere &otherSphere) const {
        float distance = glm::distance(center, otherSphere.center);
        float sumRadii = radius + otherSphere.radius;
        return distance <= sumRadii;
    }

    glm::vec3 getClosestPoint(const glm::vec3 &point) const {
        glm::vec3 direction = point - center;
        float distance = glm::length(direction);

        // If the point is inside the sphere, return the center
        if (distance < radius) {
            return center;
        }

        // Otherwise, project the point onto the sphere's surface
        return center + direction * (radius / distance);
    }
};


