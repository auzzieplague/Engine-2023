#pragma once

#include "BoundingSphere.h"

bool BoundingSphere::isCollidingWith(const BoundingSphere &otherSphere) const  {
    float distance = glm::distance(center, otherSphere.center);
    float sumRadii = radius + otherSphere.radius;
    return distance <= sumRadii;
}

glm::vec3 BoundingSphere::getClosestPoint(const glm::vec3 &point) const {
    glm::vec3 direction = point - center;
    float distance = glm::length(direction);

    // If the point is inside the sphere, return the center
    if (distance < radius) {
        return center;
    }

    // Otherwise, project the point onto the sphere's surface
    return center + direction * (radius / distance);
}

