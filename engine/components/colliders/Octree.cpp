#pragma once

#include "Octree.h"

void Octree::insert(const BoundingSphere &boundingSphere) {
    if (m_children.empty()) {
        // Leaf node
        m_objects.push_back(boundingSphere);
        if (m_objects.size() > m_maxObjectsPerNode) {
            // Subdivide node
            subdivide();
        }
    } else {
        // Non-leaf node
        for (auto &child: m_children) {
            if (child.m_boundingSphere.isCollidingWith(boundingSphere)) {
                child.insert(boundingSphere);
            }
        }
    }
}

std::vector<BoundingSphere> Octree::getCollisions(const BoundingSphere &boundingSphere) const {
    std::vector<BoundingSphere> collisions;
    if (m_boundingSphere.isCollidingWith(boundingSphere)) {
        if (m_children.empty()) {
            // Leaf node
            for (const auto &object: m_objects) {
                if (object.isCollidingWith(boundingSphere)) {
                    collisions.push_back(object);
                }
            }
        } else {
            // Non-leaf node
            for (const auto &child: m_children) {
                auto childCollisions = child.getCollisions(boundingSphere);
                collisions.insert(collisions.end(), childCollisions.begin(), childCollisions.end());
            }
        }
    }
    return collisions;
}

void Octree::subdivide() {
    // Subdivide node into eight children
    for (int i = 0; i < 8; i++) {
        auto center = m_boundingSphere.getCenter() +
                      m_boundingSphere.getRadius() * glm::vec3(
                              (i & 1) ? 0.5f : -0.5f,
                              (i & 2) ? 0.5f : -0.5f,
                              (i & 4) ? 0.5f : -0.5f);
        BoundingSphere childBoundingSphere(center, m_boundingSphere.getRadius() / 2.0f);
        m_children.emplace_back(childBoundingSphere, m_maxObjectsPerNode);
    }
    // Move objects to children
    for (auto &object: m_objects) {
        for (auto &child: m_children) {
            if (child.m_boundingSphere.isCollidingWith(object)) {
                child.insert(object);
            }
        }
    }
    m_objects.clear();
}
