#pragma once

#include "Collider.h"

bool Collider::containsPoint(const glm::vec3 &point) const {
    // Use the separating axis theorem to determine if the point is inside the convex hull

    for (int i = 0; i < m_vertices.size(); i++) {
        int j = (i + 1) % m_vertices.size();

        glm::vec3 edge = m_vertices[j] - m_vertices[i];
        glm::vec3 normal = glm::normalize(glm::cross(edge, point - m_vertices[i]));

        // Find the projection of the point onto the normal
        float projection = glm::dot(normal, point);

        // Find the min and max projection of the convex hull onto the normal
        float minProjection = glm::dot(normal, m_vertices[0]);
        float maxProjection = minProjection;

        for (int k = 1; k < m_vertices.size(); k++) {
            float p = glm::dot(normal, m_vertices[k]);

            if (p < minProjection) {
                minProjection = p;
            } else if (p > maxProjection) {
                maxProjection = p;
            }
        }

        if (projection < minProjection || projection > maxProjection) {
            // The point is outside the convex hull
            return false;
        }
    }

    // The point is inside the convex hull
    return true;
}

ColliderConfig Collider::getConfig() const {
    return this->m_config;
}

