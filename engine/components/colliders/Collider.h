#include <glm/glm.hpp>
#include <vector>
#include "../Geometry.h"
#include "BoundingSphere.h"
#include "BoundingBox.h"


class Collider {

    enum ColliderType {
        CT_Box,
        CT_Sphere,
        CT_Capsule,
        CT_Mesh,
        CT_ConvexMesh,
        CT_General,
        CT_Terrain,
    };

private:
    BoundingSphere m_sphere; // m_center is world m_position
    BoundingBox m_aabb;// world coordinate comparison
    std::vector<glm::vec3> m_vertices; // needs to contain all model sub meshes

    ColliderType collisionType;

public:
    explicit Collider() {
        collisionType = CT_General;
    };

    /**
     * update the centers of the bounding volumes
     * @return
     */
    virtual void update(glm::vec3 offsetChange){
        /**
         * shift m_position of m_sphere m_center ... note m_center is not origin of model so we can just set m_position
         * similarly we need to shift the min and max corners of the bounding box
         *
         * where the object scales, we will need to recalculate the whole volume as corners and
         */

        m_sphere.moveCenter(offsetChange);
    }

    virtual void rebuild(Mesh * mesh){
        /**
         * todo shift m_position of m_sphere m_center ... note m_center is not origin of model so we can just set m_position
         * similarly we need to shift the min and max corners of the bounding box
         *
         * where the object scales, we will need to recalculate the whole volume as corners and
         */

        m_sphere.findRadiusAndCenter(mesh->positions);
        m_aabb.findMinMaxCorners(mesh->positions);
    }



    virtual bool isColliding(Collider *otherCollider) {
        // m_aabb and m_sphere are initialised in model constructor

        if (m_sphere.isCollidingWith(otherCollider->m_sphere)) {
            return true;
        };


        // todo check m_aabb

        // todo check mesh - need to add collision mesh to collider as it's not the same as actual mesh
        return false;
    }

    [[nodiscard]] bool containsPoint(const glm::vec3 &point) const;
};