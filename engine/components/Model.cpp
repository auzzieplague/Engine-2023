#pragma once

#include "Model.h"
#include "Terrain.h"

Model *Model::createFromGeometry(Geometry::ShapeType shape, GeometryConfig config) {
    auto *model = new Model();
    model->mMesh = new Geometry();
    switch (shape) {
        default:
            Debug::show("unsupported shape requested by model");
            break;
        case Geometry::ShapeType::Cube :
            dynamic_cast<Geometry *>(model->mMesh)->buildCube(config);
            break;
        case Geometry::ShapeType::Sphere :
            dynamic_cast<Geometry *>(model->mMesh)->buildSphere(config);
            break;
        case Geometry::ShapeType::Terrain :
            // here we're treating terrain as a model just for testing purposes
            dynamic_cast<Geometry *>(model->mMesh)->buildTerrain(config);
            break;
        case Geometry::ShapeType::Dome :
            dynamic_cast<Geometry *>(model->mMesh)->buildDome(config);
            break;
        case Geometry::ShapeType::Torus :
            dynamic_cast<Geometry *>(model->mMesh)->buildTorus(config);
            break;
        case Geometry::ShapeType::Capsule :
            dynamic_cast<Geometry *>(model->mMesh)->buildCapsule(config);
            break;
        case Geometry::ShapeType::Cone :
            dynamic_cast<Geometry *>(model->mMesh)->buildCone(config);
            break;
    }
    return model;
}

void Model::setPosition(glm::vec3 newPosition) {
    // note: it's a prerequisite that you setCollider() before moving things around
    if (this->mCollider) {
        this->mCollider->update(m_transform.getPosition() - newPosition);
    }
    Component::setPosition(newPosition);
}

void Model::setScale(glm::vec3 scale) {
    Component::setScale(scale);
    /* when scaling we will need to rebuild and reset m_vertices of colliders as centers
     * and corners will have changed
     */
    if (this->mCollider) {
        // physx setTransform can replace this - if physics is running
//        this->mCollider->rebuild(mMesh);
    }
}

void Model::setRotation(glm::vec3 rotation) {
    Component::setRotation(rotation);
    /*
     * when rotating we will need to rebuild and reset m_vertices of colliders as centers
     * and corners will have changed
     */
    if (this->mCollider) {
        // physx setTransform can replace this - if physics is running
        this->mCollider->rebuild(mMesh);
    }
}

void Model::applyForce(glm::vec3 force) const{
    // todo: check if dynamic .. probably subclass dynamic and static models so no checking required
    if (!mPhysicsBody) {
        return;
    }

    dynamic_cast<physx::PxRigidDynamic *>(this->mPhysicsBody)->addForce(physx::PxVec3(force.x, force.y, force.z));
}


void Model::applyImpulse(glm::vec3 force) const{
    // todo: check if dynamic .. probably subclass dynamic and static models so no checking required
    if (!mPhysicsBody) {
        return;
    }

    dynamic_cast<physx::PxRigidDynamic *>(this->mPhysicsBody)->addForce(physx::PxVec3(force.x, force.y, force.z), physx::PxForceMode::eIMPULSE);
}

void Model::setCollider(ColliderConfig config)  {
    // note: model would need to be set collidable before adding to scene, to be added to correct <vector>
    mCollider = new Collider(config);
    mCollider->rebuild(mMesh);
    this->mCollider->update(-m_transform.getPosition());

    // get box of meshes
    // getRadius of meshes
}

void Model::applyPxTransform(const physx::PxTransform &pxTransform) {

    //todo - will replace isColliding function with physX checks, but until then we will need to apply the position updates to the mCollider
    mCollider->rebuild(mMesh);
    this->mCollider->update(-m_transform.getPosition());

    if (!mPhysicsBody) {
        return;
    }
    this->m_transform.applyPxTransform(pxTransform);
}

void Model::getMeshFromHeightMap(std::string name) {
    this->mMesh = AssetManager::getMeshFromHeightMap(name,1,1);
}

physx::PxTransform Model::getPxTransform() {
    return this->m_transform.getPxTransform();
}
