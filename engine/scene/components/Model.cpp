#pragma once

#include "Model.h"

void Model::applyForce(glm::vec3 force) const {
    // todo: check if dynamic .. probably subclass dynamic and static models so no checking required
    if (!mPhysicsBody) {
        return;
    }

    dynamic_cast<physx::PxRigidDynamic *>(this->mPhysicsBody)->addForce(physx::PxVec3(force.x, force.y, force.z));
}

void Model::addChild(Component *child) {
    // meshes get handled on root mesh and put into mesh tree
    if (child->getType() == ObjectType::OT_Mesh) {
        if (this->mRootMesh == nullptr) {
            mRootMesh = dynamic_cast<Mesh *>(child);
        } else {
            mRootMesh->addMesh(dynamic_cast<Mesh *>(child));
        }
        child->rootComponent = this->rootComponent ? this->rootComponent : this;
        child->parentComponent = this;
    } else {
        Component::addChild(child);
    }
}

void Model::applyImpulse(glm::vec3 force) const {
    // todo: check if dynamic .. probably subclass dynamic and static models so no checking required
    if (!mPhysicsBody) {
        return;
    }

    dynamic_cast<physx::PxRigidDynamic *>(this->mPhysicsBody)->addForce(physx::PxVec3(force.x, force.y, force.z),
                                                                        physx::PxForceMode::eIMPULSE);
}

void Model::applyPxTransform(const physx::PxTransform &pxTransform) {

}

void Model::getMeshFromHeightMap(std::string name) {
    this->mRootMesh = Mesh::getMeshFromHeightMap(name, 1, 1);
    this->mRootMesh->parentComponent = this;
    this->mCollisionMesh = mRootMesh;
    this->childComponents.push_back(mRootMesh);
}

physx::PxTransform Model::getPxTransform() {
    return this->localTransform.getPxTransform();
}

void Model::setMaterial(Material material) {
    this->mRootMesh->setMaterial(material);
}

void Model::setCollisionMesh(Mesh *mesh) {
    this->mCollisionMesh = mesh;
    this->childComponents.push_back(mCollisionMesh);
}

Mesh *Model::getCollisionMesh() {
    return this->mCollisionMesh;
}

Mesh *Model::getRootMesh() {
    return this->mRootMesh;
}

void Model::onTransformChange() {
    Component::onTransformChange();
    if (!this->mPhysicsBody) return;

    this->mPhysicsBody->setGlobalPose(localTransform.getPxTransform());
}

void Model::pause() {
    Component::pause();
    if (!isDynamic() || !mPhysicsBody->is<physx::PxRigidDynamic>()) return;

    auto *actor = dynamic_cast<physx::PxRigidDynamic *>(this->mPhysicsBody);
    actor->setActorFlag(physx::PxActorFlag::eDISABLE_SIMULATION, true);
}

void Model::resume() {
    Component::resume();
    if (!isDynamic() || !mPhysicsBody->is<physx::PxRigidDynamic>()) return;

    auto *actor = dynamic_cast<physx::PxRigidDynamic *>(this->mPhysicsBody);
    actor->setActorFlag(physx::PxActorFlag::eDISABLE_SIMULATION, false);
    actor->wakeUp();
    Debug::show("resumed model physics");
}

void Model::autoScale() {

}

void Model::autoPhysics() {
 // todo: build convex hull - grab all sub mesh vertices
}
