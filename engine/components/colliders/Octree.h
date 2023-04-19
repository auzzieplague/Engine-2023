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
    void *m_object_ptr;
public:
    [[nodiscard]] void *getObjectPtr() const;

    void setObjectPtr(void *objectPtr);

private:
    void subdivide();

public:
    explicit Octree(const BoundingSphere &boundingSphere, int maxObjectsPerNode = 8)
            : m_boundingSphere(boundingSphere), m_maxObjectsPerNode(maxObjectsPerNode) { m_object_ptr = nullptr; }

    void insert(const BoundingSphere &boundingSphere);

    void insert(const BoundingSphere &boundingSphere, void *object_ptr) {
        m_object_ptr = object_ptr;
        insert(boundingSphere);
    };

    [[nodiscard]] std::vector<BoundingSphere> getCollisions(const BoundingSphere &boundingSphere) const;

};