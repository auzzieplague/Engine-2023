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

public:

    BoundingSphere sphere; // center is world position
    BoundingBox aabb;// world cordinate comparison
    std::vector<glm::vec3> m_vertices; // needs to contain all model submeshes

    ColliderType collisionType;

    explicit Collider() {
        collisionType = CT_General;
    };

    /**
     * update the centers of the bounding volumes
     * @return
     */
    virtual void update(glm::vec3 offsetChange){
        /**
         * shift position of sphere center ... note center is not origin of model so we can just set position
         * similarly we need to shift the min and max corners of the bounding box
         *
         * where the object scales, we will need to recalculate the whole volume as corners and
         */

        sphere.moveCenter(offsetChange);
    }

    virtual void rebuild(Mesh * mesh){
        /**
         * todo shift position of sphere center ... note center is not origin of model so we can just set position
         * similarly we need to shift the min and max corners of the bounding box
         *
         * where the object scales, we will need to recalculate the whole volume as corners and
         */

        sphere.findRadiusAndCenter(mesh->positions);
        aabb.findMinMaxCorners(mesh->positions);
    }



    virtual bool isColliding(Collider *otherCollider) {
        // aabb and sphere are initialised in model constructor

        if (sphere.isCollidingWith(otherCollider->sphere)) {
            return true;
        };


        // todo check aabb

        // todo check mesh - need to add collision mesh to collider as it's not the same as actual mesh
        return false;
    }

    [[nodiscard]] bool containsPoint(const glm::vec3 &point) const;
};