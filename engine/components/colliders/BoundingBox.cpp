#pragma once

#include "BoundingBox.h"

bool BoundingBox::isCollidingWith(const BoundingBox &otherAABB) const {
    return (m_maxCorner.x >= otherAABB.m_minCorner.x && m_minCorner.x <= otherAABB.m_maxCorner.x) &&
           (m_maxCorner.y >= otherAABB.m_minCorner.y && m_minCorner.y <= otherAABB.m_maxCorner.y) &&
           (m_maxCorner.z >= otherAABB.m_minCorner.z && m_minCorner.z <= otherAABB.m_maxCorner.z);
}

glm::vec3 BoundingBox::getClosestPoint(const glm::vec3 &point) const {
    glm::vec3 closestPoint;

    for (int i = 0; i < 3; i++) {
        float value = point[i];

        if (value < m_minCorner[i]) {
            value = m_minCorner[i];
        } else if (value > m_maxCorner[i]) {
            value = m_maxCorner[i];
        }

        closestPoint[i] = value;
    }
    return closestPoint;
}

void BoundingBox::findMinMaxCorners(const std::vector<glm::vec3> &vertices) {
    if (vertices.empty()) {
        m_minCorner = glm::vec3(0.0f);
        m_maxCorner = glm::vec3(0.0f);
        return;
    }

    m_minCorner = m_maxCorner = vertices[0];

    for (int i = 1; i < vertices.size(); i++) {
        glm::vec3 vertex = vertices[i];

        if (vertex.x < m_minCorner.x) {
            m_minCorner.x = vertex.x;
        } else if (vertex.x > m_maxCorner.x) {
            m_maxCorner.x = vertex.x;
        }

        if (vertex.y < m_minCorner.y) {
            m_minCorner.y = vertex.y;
        } else if (vertex.y > m_maxCorner.y) {
            m_maxCorner.y = vertex.y;
        }

        if (vertex.z < m_minCorner.z) {
            m_minCorner.z = vertex.z;
        } else if (vertex.z > m_maxCorner.z) {
            m_maxCorner.z = vertex.z;
        }
    }
}