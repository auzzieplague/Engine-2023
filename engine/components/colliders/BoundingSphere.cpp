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

bool BoundingSphere::isCollidingWith(const TerrainMesh &terrain) const {

    /// subdivide the terrain mesh using octree
    /// actually - all meshes can use octree to partition the faces and vertices


    // Check if the sphere is completely outside the bounding box of the mesh
//    if (center.x - radius > terrain.max_x ||
//        center.x + radius < terrain.min_x ||
//        center.y - radius > terrain.max_y ||
//        center.y + radius < terrain.min_y ||
//        center.z - radius > terrain.max_z ||
//        center.z + radius < terrain.min_z) {
//        return false;
//    }

    // Check if the sphere intersects any of the triangles in the mesh
//    for (const auto &face : terrain.faces) {
//        // Calculate the normal vector of the face
//        glm::vec3 v1 = terrain.vertices[face[0]];
//        glm::vec3 v2 = terrain.vertices[face[1]];
//        glm::vec3 v3 = terrain.vertices[face[2]];
//        glm::vec3 normal = glm::normalize(glm::cross(v2 - v1, v3 - v1));
//
//        // Calculate the distance between the center of the sphere and the plane of the face
//        float distance = glm::dot(normal, center - v1);
//
//        // If the sphere is on the opposite side of the plane from the normal vector, it cannot intersect the face
//        if (distance > radius) {
//            continue;
//        }
//
//        // Project the sphere's center onto the plane of the face
//        glm::vec3 projected_center = center - distance * normal;
//
//        // Calculate the barycentric coordinates of the projected center in relation to the face
//        glm::vec3 barycentric = glm::inverse(glm::mat3(v1, v2, v3)) * projected_center;
//
//        // If the projected center is inside the triangle and closer than the sphere radius, there is a collision
//        if (barycentric.x >= 0 && barycentric.x <= 1 &&
//            barycentric.y >= 0 && barycentric.y <= 1 &&
//            barycentric.z >= 0 && barycentric.z <= 1 &&.



 +
//            glm::distance(projected_center, center) <= radius) {
//            return true;
//        }
//    }

    return false;
}

float BoundingSphere::getRadius() const {
    return radius;
}

void BoundingSphere::setRadius(float radius) {
    BoundingSphere::radius = radius;
}

const glm::vec3 &BoundingSphere::getCenter() const {
    return center;
}

void BoundingSphere::setCenter(const glm::vec3 &center) {
    BoundingSphere::center = center;
}

void BoundingSphere::findRadiusAndCenter(const std::vector<glm::vec3> &vertices) {
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

void BoundingSphere::moveCenter(const glm::vec3 &offset) {
    this->center+=offset;
}
