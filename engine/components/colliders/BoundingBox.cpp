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

void BoundingBox::findMinMaxCorners(const std::vector<glm::vec3> &vertices) {
    if (vertices.empty()) {
        minCorner = glm::vec3(0.0f);
        maxCorner = glm::vec3(0.0f);
        return;
    }

    minCorner = maxCorner = vertices[0];

    for (int i = 1; i < vertices.size(); i++) {
        glm::vec3 vertex = vertices[i];

        if (vertex.x < minCorner.x) {
            minCorner.x = vertex.x;
        } else if (vertex.x > maxCorner.x) {
            maxCorner.x = vertex.x;
        }

        if (vertex.y < minCorner.y) {
            minCorner.y = vertex.y;
        } else if (vertex.y > maxCorner.y) {
            maxCorner.y = vertex.y;
        }

        if (vertex.z < minCorner.z) {
            minCorner.z = vertex.z;
        } else if (vertex.z > maxCorner.z) {
            maxCorner.z = vertex.z;
        }
    }
}