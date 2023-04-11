#pragma once

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <vector>

/**
 * @author Michael.Whinfrey
 */
class BoundingSphere {
    glm::vec3 center;
    float radius;

    BoundingSphere(const glm::vec3 &center, float radius) : center(center), radius(radius) {};
public:
    BoundingSphere() : center(0.0f), radius(0.0f) {}

    [[nodiscard]] bool isCollidingWith(const BoundingSphere &otherSphere) const;

    glm::vec3 getClosestPoint(const glm::vec3 &point) const ;

    void findRadiusAndCenter(const std::vector<glm::vec3>& vertices) {
        if (vertices.empty()) {
            center = glm::vec3(0.0f);
            radius = 0.0f;
            return;
        }

        glm::vec3 sum(0.0f);
        for (const auto& vertex : vertices) {
            sum += vertex;
        }

        center = sum / static_cast<float>(vertices.size());

        float maxDistanceSq = 0.0f;
        for (const auto& vertex : vertices) {
            float distanceSq = glm::distance(vertex, center);
            distanceSq = distanceSq * distanceSq;
            if (distanceSq > maxDistanceSq) {
                maxDistanceSq = distanceSq;
            }
        }

        radius = std::sqrt(maxDistanceSq);
    }
};


