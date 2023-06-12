#pragma once

#include <PxRigidActor.h>
#include "Component.h"
#include "meshes/Mesh.h"
#include "colliders/Collider.h"

class Model : public Component {

public:
    Mesh *rootMesh{};
    Mesh *collisionMesh{};
    Collider *mCollider{};
    physx::PxRigidActor *mPhysicsBody{};

    ObjectType getType() override {
        return ObjectType::OT_Model;
    };

    static Model *createFromGeometry(Geometry::ShapeType shape, GeometryConfig config = {});

    void addChild(Component *child) override; // need to add meshes to meshtree

    // todo setCollider(level) radial, box, rootMesh
    virtual void setCollider(ColliderConfig config);
//
//    /**
//     * use model->setLocalPosition to correctly update colliders and underlying objects
//     * using rootMesh transform
//     */
//    void setLocalPosition(glm::vec3) override;
//
//    void setLocalScale(glm::vec3) override;
//
//    void setLocalRotation(glm::vec3) override;

    // physics handlers
    void applyPxTransform(const physx::PxTransform &pxTransform);

    physx::PxTransform getPxTransform();

    void applyForce(glm::vec3 force = {}) const;

    void applyImpulse(glm::vec3 force) const;

    void getMeshFromHeightMap(std::string);

    void setMaterial(Material material);
};


