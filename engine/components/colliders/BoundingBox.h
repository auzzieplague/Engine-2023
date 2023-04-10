#pragma once

#include <glm/vec3.hpp>

/**
 * @author Michael.Whinfrey
 */
class BoundingBox {
    glm::vec3 minCorner;
    glm::vec3 maxCorner;


    BoundingBox(const glm::vec3 &minCorner, const glm::vec3 &maxCorner) : minCorner(minCorner), maxCorner(maxCorner) {}

    // Returns true if this AABB is colliding with the given otherAABB
    [[nodiscard]] bool isCollidingWith(const BoundingBox &otherAABB) const;

    [[nodiscard]] glm::vec3 getClosestPoint(const glm::vec3 &point) const;

public:
    BoundingBox() : minCorner(0.0f), maxCorner(0.0f) {}
};


