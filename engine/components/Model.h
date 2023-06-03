#pragma once

#include <PxRigidActor.h>
#include "Component.h"
#include "meshes/Mesh.h"
#include "colliders/Collider.h"

class Model : public Component {

public:
    Mesh *mMesh{};
    Collider *mCollider{};
    physx::PxRigidActor* mPhysicsBody{};

    ObjectType getType() override {
        return ObjectType::OT_Model;
    };

    static Model *createFromGeometry(Geometry::ShapeType shape, GeometryConfig config = {});

    // todo setCollider(level) radial, box, mMesh
    virtual void setCollider(ColliderConfig config);

    /**
     * use model->setPosition to correctly update colliders and underlying objects
     */
    void setPosition(glm::vec3) override;

    void setScale(glm::vec3) override;

    void setRotation(glm::vec3) override;

    // physics handlers
    void applyPxTransform(const physx::PxTransform& pxTransform);

    physx::PxTransform getPxTransform();

    void applyForce(glm::vec3 force = {}) const;

    void applyImpulse(glm::vec3 force) const;

    void getMeshFromHeightMap(std::string);

    void setMaterial(Material material);
};


