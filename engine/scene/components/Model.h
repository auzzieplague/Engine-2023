#pragma once

#include <PxRigidActor.h>
#include "Component.h"
#include "meshes/Mesh.h"

class Model : public Component {

public:
    Mesh *mRootMesh{};
    Mesh *mCollisionMesh;
    Collider *mCollider{};
    physx::PxRigidActor *mPhysicsBody{};
    physx::PxTransform previousGlobalPose{};

    /// Overrides
    ObjectType getType() override {
        return ObjectType::OT_Model;
    };

    [[nodiscard]] bool isDynamic() const {

        return true;
    }

    void onTransformChange() override;

    void pause() override;

    void resume() override;


    void setCollisionMesh(Mesh *mesh);

    Mesh *getCollisionMesh();

    Mesh *getRootMesh();

    // physics handlers
    void applyPxTransform(const physx::PxTransform &pxTransform);

    physx::PxTransform getPxTransform();

    void applyForce(glm::vec3 force = {}) const;

    void applyImpulse(glm::vec3 force) const;

    void getMeshFromHeightMap(std::string);

    void setMaterial(Material material);

    void autoScale();

    void autoPhysics();

    void addChild(Component *child) override;
};

