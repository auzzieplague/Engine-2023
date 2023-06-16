#pragma once

#include "Model.h"
#include "Terrain.h"

Model *Model::createFromGeometry(Geometry::ShapeType shape, GeometryConfig config) {
    auto *model = new Model();
    model->mRootMesh = new Geometry();

    std::string shapeText = "";
    switch (shape) {
        default:
            Debug::show("unsupported shape requested by model");
            break;
        case Geometry::ShapeType::Cube :
            shapeText = "Cube";
            dynamic_cast<Geometry *>(model->mRootMesh)->buildCube(config);
            break;
        case Geometry::ShapeType::Sphere :
            shapeText = "Sphere";
            dynamic_cast<Geometry *>(model->mRootMesh)->buildSphere(config);
            break;
        case Geometry::ShapeType::Terrain :
            shapeText = "Terrain";
            // here we're treating terrain as a model just for testing purposes
            dynamic_cast<Geometry *>(model->mRootMesh)->buildTerrain(config);
            break;
        case Geometry::ShapeType::Dome :
            shapeText = "Dome";
            dynamic_cast<Geometry *>(model->mRootMesh)->buildDome(config);
            break;
        case Geometry::ShapeType::Torus :
            shapeText = "Torus";
            dynamic_cast<Geometry *>(model->mRootMesh)->buildTorus(config);
            break;
        case Geometry::ShapeType::Capsule :
            shapeText = "Capsule";
            dynamic_cast<Geometry *>(model->mRootMesh)->buildCapsule(config);
            break;
        case Geometry::ShapeType::Cone :
            shapeText = "Cone";
            dynamic_cast<Geometry *>(model->mRootMesh)->buildCone(config);
            break;
        case Geometry::ShapeType::Quad :
            shapeText = "Quad";
            dynamic_cast<Geometry *>(model->mRootMesh)->buildQuad(config);
            break;
    }

//    model->mRootMesh->calculateNormals();
    model->childComponents.push_back(model->mRootMesh);
//    model->addChild(model->mRootMesh);
    // check if model has UVs and Normals, if not, build them
    if (model->mRootMesh->getUVs().size() == 0) {
        throw std::runtime_error("missing UVs for shape:" + shapeText);
    }
    if (model->mRootMesh->getNormals().size() == 0) {
        throw std::runtime_error("missing Normals for shape:" + shapeText);
    }

    /// for geometry we're initially using the root mesh as the collision mesh
    model->mCollisionMesh = model->mRootMesh;
    return model;
}

void Model::applyForce(glm::vec3 force) const {
    // todo: check if dynamic .. probably subclass dynamic and static models so no checking required
    if (!mPhysicsBody) {
        return;
    }

    dynamic_cast<physx::PxRigidDynamic *>(this->mPhysicsBody)->addForce(physx::PxVec3(force.x, force.y, force.z));
}


void Model::applyImpulse(glm::vec3 force) const {
    // todo: check if dynamic .. probably subclass dynamic and static models so no checking required
    if (!mPhysicsBody) {
        return;
    }

    dynamic_cast<physx::PxRigidDynamic *>(this->mPhysicsBody)->addForce(physx::PxVec3(force.x, force.y, force.z),
                                                                        physx::PxForceMode::eIMPULSE);
}

void Model::setCollider(ColliderConfig config) {
    if (!mCollisionMesh) {
        mCollisionMesh = mRootMesh;
    }
    // note: model would need to be set collidable before adding to scene, to be added to correct <vector>
    mCollider = new Collider(config);
    mCollider->rebuild(mCollisionMesh);
    this->mCollider->updatePosition(-localTransform.getPosition());
    this->mCollider->updateSize(this->getLocalScale());
}

void Model::applyPxTransform(const physx::PxTransform &pxTransform) {

    // todo - update world coordinates not local coordinates
    // todo - swap to collision mesh instead of root mesh
    // todo -

    //todo - will replace isColliding function with physX checks, but until then we will need to apply the position updates to the mCollider
    mCollider->rebuild(mCollisionMesh);
    this->mCollider->updatePosition(-worldTransform.getPosition());

    if (!mPhysicsBody) {
        return;
    }

    // transform being handled by physics so just update the combined value ready for rendering
    this->finalTransform.applyPxTransform(pxTransform);
    updateChildTransforms();
}

void Model::getMeshFromHeightMap(std::string name) {
    this->mRootMesh = AssetManager::getMeshFromHeightMap(name, 1, 1);
    this->mCollisionMesh = mRootMesh;
    this->childComponents.push_back(mRootMesh);
    updateFinalTransform();
}

physx::PxTransform Model::getPxTransform() {
    return this->finalTransform.getPxTransform();
}

void Model::setMaterial(Material material) {
    this->mRootMesh->setMaterial(material);
}

void Model::addChild(Component *child) {
    // if were adding a mesh, then we'll need to nest it under the root mesh
    if (child->getType() == ObjectType::OT_Mesh) {
        mRootMesh->addChild(child);
    } else {
        Component::addChild(child);
    }
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