#include <glm/glm.hpp>
#include <vector>
#include "../Geometry.h"
#include "BoundingSphere.h"
#include "BoundingBox.h"


class Collider {

    enum ColliderType {
        Box,
        Sphere,
        Capsule,
        Mesh,
        ConvexMesh,
        General,
        Terrain
    };

public:

    BoundingSphere sphere;
    BoundingBox aabb;
    std::vector<glm::vec3> m_vertices; // needs to contain all model submeshes

    ColliderType collisionType;

    explicit Collider() {
        collisionType = General;
    };

    virtual bool isColliding(Collider *otherCollider) {
        // check aabb and circle exist
        // check circle
        // check aabb
        return false;
    }

    [[nodiscard]] bool containsPoint(const glm::vec3 &point) const;
};