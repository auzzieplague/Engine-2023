#pragma once

#include "BoundingBox.h"

bool BoundingBox::isCollidingWith(const BoundingBox &otherAABB) const {
    return (maxCorner.x >= otherAABB.minCorner.x && minCorner.x <= otherAABB.maxCorner.x) &&
           (maxCorner.y >= otherAABB.minCorner.y && minCorner.y <= otherAABB.maxCorner.y) &&
           (maxCorner.z >= otherAABB.minCorner.z && minCorner.z <= otherAABB.maxCorner.z);
}

glm::vec3 BoundingBox::getClosestPoint(const glm::vec3 &point) const {
    glm::vec3 closestPoint;

    for (int i = 0; i < 3; i++) {
        float value = point[i];

        if (value < minCorner[i]) {
            value = minCorner[i];
        } else if (value > maxCorner[i]) {
            value = maxCorner[i];
        }

        closestPoint[i] = value;
    }
    return closestPoint;
}
