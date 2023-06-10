#pragma once

#include <PxRigidActor.h>
#include "Component.h"
#include "meshes/Mesh.h"
#include "colliders/Collider.h"

class Model : public Component {

public:
    Mesh *rootMesh{};
    Collider *mCollider{};
    physx::PxRigidActor* mPhysicsBody{};

    ObjectType getType() override {
        return ObjectType::OT_Model;
    };

    static Model *createFromGeometry(Geometry::ShapeType shape, GeometryConfig config = {});

    // todo setCollider(level) radial, box, rootMesh
    virtual void setCollider(ColliderConfig config);

    /**
     * use model->setLocalPosition to correctly update colliders and underlying objects
     * using rootMesh transform
     */
    void setLocalPosition(glm::vec3) override;
    glm::vec3 getLocalPosition() override;

    void setScale(glm::vec3) override;

    void setLocalRotation(glm::vec3) override;
    void rotateX(float degrees);
    void rotateY(float degrees);
    void rotateZ(float degrees);

    // physics handlers
    void applyPxTransform(const physx::PxTransform& pxTransform);

    physx::PxTransform getPxTransform();

    void applyForce(glm::vec3 force = {}) const;

    void applyImpulse(glm::vec3 force) const;

    void getMeshFromHeightMap(std::string);

    void setMaterial(Material material);
};


