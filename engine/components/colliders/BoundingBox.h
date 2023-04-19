#pragma once

#include <glm/vec3.hpp>
#include <vector>

/**
 * @author Michael.Whinfrey
 */
class BoundingBox {
private:
    glm::vec3 m_minCorner;
    glm::vec3 m_maxCorner;
public:
    BoundingBox() : m_minCorner(0.0f), m_maxCorner(0.0f) {}

    BoundingBox(const glm::vec3 &minCorner, const glm::vec3 &maxCorner) : m_minCorner(minCorner),
                                                                          m_maxCorner(maxCorner) {}

    void findMinMaxCorners(const std::vector<glm::vec3> &vertices);

    void moveCorners(glm::vec3 offset)
    {
        m_minCorner-=offset;
        m_maxCorner-=offset;
    }

    // Returns true if this AABB is colliding with the given otherAABB
    [[nodiscard]] bool isCollidingWith(const BoundingBox &otherAABB) const;

    [[nodiscard]] glm::vec3 getClosestPoint(const glm::vec3 &point) const;
};


