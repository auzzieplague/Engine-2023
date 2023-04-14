#pragma once


#include <vector>
#include "BoundingSphere.h"

/**
 * @author Michael.Whinfrey
 */
class Octree {
private:
    BoundingSphere m_boundingSphere;
    int m_maxObjectsPerNode;
    std::vector<BoundingSphere> m_objects;
    std::vector<Octree> m_children;

    void subdivide();

public:
    Octree(const BoundingSphere &boundingSphere, int maxObjectsPerNode = 8)
            : m_boundingSphere(boundingSphere), m_maxObjectsPerNode(maxObjectsPerNode) {}

    void insert(const BoundingSphere &boundingSphere);

    std::vector<BoundingSphere> getCollisions(const BoundingSphere &boundingSphere) const;

};