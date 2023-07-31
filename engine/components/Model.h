#pragma once

#include <PxRigidActor.h>
#include "Component.h"
#include "meshes/Mesh.h"
#include "colliders/Collider.h"

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
        if (!this->mPhysicsBody) return false;
        if (this->mCollider->m_config.type != ColliderConfig::Dynamic) return false;
        return true;
    }

    void onTransformChange() override;

    void pause() override;

    void resume() override;

    static Model *createWithGeometry(Geometry::ShapeType shape, GeometryConfig config = {});

    virtual void setCollider(ColliderConfig config);

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
};


