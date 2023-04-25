#include <glm/glm.hpp>
#include <vector>
#include "../Geometry.h"
#include "BoundingSphere.h"
#include "BoundingBox.h"


struct ColliderConfig {
    enum CollisionShape {
        Box, Sphere, HeightMap
    };

    CollisionShape shape = Box;

    enum CollisionType {
        Static, Dynamic
    };

    CollisionType type = Static;

    struct MaterialConfig {
        float staticFriction = 0.5;
        float dynamicFriction = 0.5;
        float restitution = 0.6;
    };

    MaterialConfig material {};

    float size= 0.5;
};

class Collider {

private:
    BoundingSphere m_sphere; // m_center is world m_position
    BoundingBox m_aabb;// world coordinate comparison
    std::vector<glm::vec3> m_vertices; // the hull needs to contain all model sub meshes
public:
    ColliderConfig m_config;
    explicit Collider(ColliderConfig config) {
        m_config = config;
    };

    [[nodiscard]] ColliderConfig getConfig() const;

    /**
     * update the centers of the bounding volumes
     * @return
     */
    virtual void update(glm::vec3 offsetChange) {
        /**
         * shift m_position of m_sphere m_center ... note m_center is not origin of model so we can just set m_position
         * similarly we need to shift the min and max corners of the bounding box
         *
         * where the object scales, we will need to recalculate the whole volume as corners and
         */

        m_sphere.moveCenter(offsetChange);
        m_aabb.moveCorners(offsetChange);
    }

    virtual void rebuild(Mesh *mesh) {
        /**
         * todo shift m_position of m_sphere m_center ... note m_center is not origin of model so we can just set m_position
         * similarly we need to shift the min and max corners of the bounding box
         *
         * where the object scales, we will need to recalculate the whole volume as corners and
         */

        m_sphere.findRadiusAndCenter(mesh->m_vertices);
        m_aabb.findMinMaxCorners(mesh->m_vertices);
    }


    virtual bool isColliding(Collider *otherCollider) {
        // m_aabb and m_sphere are m_ready in model constructor

        // waterfall logic to determine not colliding.
        if (!m_sphere.isCollidingWith(otherCollider->m_sphere)) {
            return false;
        };

        // note: spheres would be i'll suited to box collision so we'll need to do some type checking

        if (!m_aabb.isCollidingWith(otherCollider->m_aabb)) {
            return false;
        };

        // octree on mMesh

        // todo check mMesh - need to add collision mMesh to mCollider as it's not the same as actual mMesh
        return true;
    }

    [[nodiscard]] bool containsPoint(const glm::vec3 &point) const;
};