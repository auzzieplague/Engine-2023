#pragma once

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <vector>

/**
 * @author Michael.Whinfrey
 */
class TerrainMesh;

class BoundingSphere {
private:
    float m_radius;
    glm::vec3 m_center;
public:
    [[nodiscard]] float getRadius() const;

    [[maybe_unused]] void setRadius(float radius);

    [[nodiscard]] const glm::vec3 &getCenter() const;

    [[maybe_unused]] void setCenter(const glm::vec3 &center);

    void moveCenter(const glm::vec3 &offset);

    BoundingSphere(const glm::vec3 &center, float radius) : m_center(center), m_radius(radius) {};

    BoundingSphere() : m_center(0.0f), m_radius(0.0f) {}

    [[nodiscard]] bool isCollidingWith(const BoundingSphere &otherSphere) const;

    [[nodiscard]] bool isCollidingWith(const TerrainMesh &terrain) const;

    [[maybe_unused]] [[nodiscard]] glm::vec3 getClosestPoint(const glm::vec3 &point) const;

    void findRadiusAndCenter(const std::vector<glm::vec3> &vertices);
};


