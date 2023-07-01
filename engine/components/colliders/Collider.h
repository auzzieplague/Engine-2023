#include <glm/glm.hpp>
#include <vector>
#include "../Geometry.h"
#include "BoundingSphere.h"
#include "BoundingBox.h"


struct ColliderConfig {
    enum CollisionShape {
        Box, Sphere, HeightMap, Mesh
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


};

class Collider {

private:
    BoundingSphere m_sphere; // m_center is world mPosition
    BoundingBox m_aabb;// world coordinate comparison
    std::vector<glm::vec3> m_vertices; // the hull needs to contain all model sub meshes
    glm::vec3 m_size{}; // used for physx objects

public:
    ColliderConfig m_config;
    explicit Collider(ColliderConfig config) {
        m_config = config;
    };

    [[nodiscard]] ColliderConfig getConfig() const;
    float getRadius(){
        return this->m_sphere.getRadius();
    }

    glm::vec3 getSize() {
        return this->m_size;
    }

    void updateSize(glm::vec3 scale = {1,1,1}) {
        // updatePosition m_size value of collider based on type
        switch (m_config.shape) {
            case m_config.Sphere:
                // radius from collider - scale from transform
                this->m_size = this->getRadius() * scale;
                break;
            case m_config.Box:
                this->m_size = (m_aabb.m_maxCorner - m_aabb.m_minCorner)*scale;
                break;
            case m_config.Mesh:
                // mesh is preloaded scaled each vertex is scaled before loading into shape
            default:
                this->m_size = {1.0f, 1.0f, 1.0f};
        }
    }

    /**
     * updatePosition the centers of the bounding volumes
     * @return
     */
    virtual void updatePosition(glm::vec3 offsetChange) {
        /**
         * shift mPosition of m_sphere m_center ... note m_center is not origin of model so we can just set mPosition
         * similarly we need to shift the min and max corners of the bounding box
         *
         * where the object scales, we will need to recalculate the whole volume as corners and
         */

        m_sphere.moveCenter(offsetChange);
        m_aabb.moveCorners(offsetChange);
    }

    virtual void rebuild(Mesh *mesh) {
        /**
         * todo shift mPosition of m_sphere m_center ... note m_center is not origin of model so we can just set mPosition
         * similarly we need to shift the min and max corners of the bounding box
         *
         * where the object scales, we will need to recalculate the whole volume as corners and
         */
        if (mesh){
            m_sphere.findRadiusAndCenter(mesh->m_vertices);
            m_aabb.findMinMaxCorners(mesh->m_vertices);
        }
    }


    virtual bool isColliding(Collider *otherCollider) {
        // m_aabb and m_sphere are mReady in model constructor

        // waterfall logic to determine not colliding.
        if (!m_sphere.isCollidingWith(otherCollider->m_sphere)) {
            return false;
        };

        // note: spheres would be i'll suited to box collision so we'll need to do some type checking

        if (!m_aabb.isCollidingWith(otherCollider->m_aabb)) {
            return false;
        };

        // octree on mRootMesh

        // todo check mRootMesh - need to add collision mRootMesh to mCollider as it's not the same as actual mRootMesh
        return true;
    }

    [[nodiscard]] bool containsPoint(const glm::vec3 &point) const;
};