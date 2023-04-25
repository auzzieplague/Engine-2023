#pragma once

#include "Model.h"

Model *Model::createFromGeometry(Geometry::ShapeType shape, GeometryConfig config) {
    auto *model = new Model();
    model->mesh = new Geometry();
    switch (shape) {
        default:
            Debug::show("unsupported shape requested by model");
            break;
        case Geometry::ShapeType::Cube :
            dynamic_cast<Geometry *>(model->mesh)->buildCube(config);
            break;
        case Geometry::ShapeType::Sphere :
            dynamic_cast<Geometry *>(model->mesh)->buildSphere(config);
            break;
        case Geometry::ShapeType::Terrain :
            dynamic_cast<Geometry *>(model->mesh)->buildTerrain(config);
            break;
        case Geometry::ShapeType::Dome :
            dynamic_cast<Geometry *>(model->mesh)->buildDome(config);
            break;
        case Geometry::ShapeType::Torus :
            dynamic_cast<Geometry *>(model->mesh)->buildTorus(config);
            break;
        case Geometry::ShapeType::Capsule :
            dynamic_cast<Geometry *>(model->mesh)->buildCapsule(config);
            break;
        case Geometry::ShapeType::Cone :
            dynamic_cast<Geometry *>(model->mesh)->buildCone(config);
            break;
    }
    return model;
}

void Model::setPosition(glm::vec3 newPosition) {
    // note: it's a prerequisite that you setCollider() before moving things around
    if (this->collider) {
        this->collider->update(m_transform.getPosition() - newPosition);
    }
    Component::setPosition(newPosition);
}

void Model::setScale(glm::vec3 scale) {
    Component::setRotation(scale);
    /* when scaling we will need to rebuild and reset m_vertices of colliders as centers
     * and corners will have changed
     */
    if (this->collider) {
        // physx setTransform can replace this - if physics is running
        this->collider->rebuild(mesh);
    }
}

void Model::setRotation(glm::vec3 rotation) {
    Component::setRotation(rotation);
    /*
     * when rotating we will need to rebuild and reset m_vertices of colliders as centers
     * and corners will have changed
     */
    if (this->collider) {
        // physx setTransform can replace this - if physics is running
        this->collider->rebuild(mesh);
    }
}

void Model::applyForce(glm::vec3 force) const{
    // todo: check if dynamic .. probably subclass dynamic and static models so no checking required
    if (!physicsBody) {
        return;
    }

    dynamic_cast<physx::PxRigidDynamic *>(this->physicsBody)->addForce(physx::PxVec3(force.x, force.y, force.z));
}


void Model::applyImpulse(glm::vec3 force) const{
    // todo: check if dynamic .. probably subclass dynamic and static models so no checking required
    if (!physicsBody) {
        return;
    }

    dynamic_cast<physx::PxRigidDynamic *>(this->physicsBody)->addForce(physx::PxVec3(force.x, force.y, force.z),physx::PxForceMode::eIMPULSE);
}

void Model::setCollider(ColliderConfig config)  {
    // note: model would need to be set collidable before adding to scene, to be added to correct <vector>
    collider = new Collider(config);
    collider->rebuild(mesh);
    this->collider->update(-m_transform.getPosition());

    // get box of meshes
    // getRadius of meshes
}

void Model::applyPxTransform(const physx::PxTransform &pxTransform) {

    //todo - will replace isColliding function with physX checks, but until then we will need to apply the position updates to the collider
    collider->rebuild(mesh);
    this->collider->update(-m_transform.getPosition());

    if (!physicsBody) {
        return;
    }
    this->m_transform.applyPxTransform(pxTransform);
}
