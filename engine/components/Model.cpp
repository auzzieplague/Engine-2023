#pragma once

#include "Model.h"
#include "Terrain.h"

Model *Model::createWithGeometry(Geometry::ShapeType shape, GeometryConfig config) {
    auto *model = new Model();
    Mesh *newMesh = new Geometry();
    newMesh->setSelectable();
    std::string shapeText = "";
    switch (shape) {
        default:
            Debug::show("unsupported shape requested by model");
            break;
        case Geometry::ShapeType::Cube :
            shapeText = "Cube";
            dynamic_cast<Geometry *>(newMesh)->buildCube(config);
            break;
        case Geometry::ShapeType::Sphere :
            shapeText = "Sphere";
            dynamic_cast<Geometry *>(newMesh)->buildSphere(config);
            break;
        case Geometry::ShapeType::Terrain :
            shapeText = "Terrain";
            // here we're treating terrain as a model just for testing purposes
            dynamic_cast<Geometry *>(newMesh)->buildTerrain(config);
            break;
        case Geometry::ShapeType::Dome :
            shapeText = "Dome";
            dynamic_cast<Geometry *>(newMesh)->buildDome(config);
            break;
        case Geometry::ShapeType::Torus :
            shapeText = "Torus";
            dynamic_cast<Geometry *>(newMesh)->buildTorus(config);
            break;
        case Geometry::ShapeType::Capsule :
            shapeText = "Capsule";
            dynamic_cast<Geometry *>(newMesh)->buildCapsule(config);
            break;
        case Geometry::ShapeType::Cone :
            shapeText = "Cone";
            dynamic_cast<Geometry *>(newMesh)->buildCone(config);
            break;
        case Geometry::ShapeType::Quad :
            shapeText = "Quad";
            dynamic_cast<Geometry *>(newMesh)->buildQuad(config);
            break;
    }

    newMesh->setName(shapeText);
//    newMesh->calculateNormals();
//    model->childComponents.push_back(newMesh);
//    model->addChild(newMesh);
    // check if model has UVs and Normals, if not, build them
    if (newMesh->getUVs().size() == 0) {
        throw std::runtime_error("missing UVs for shape:" + shapeText);
    }
    if (newMesh->getNormals().size() == 0) {
        throw std::runtime_error("missing Normals for shape:" + shapeText);
    }

    /// for geometry we're initially using the root mesh as the collision mesh
    model->mCollisionMesh = newMesh;
    model->mRootMesh = newMesh;
    newMesh->parentComponent = model;
    model->addChild(newMesh);
    return model;
}

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
    //todo - will replace isColliding function with physX checks, but until then we will need to apply the position updates to the mCollider
    mCollider->rebuild(mCollisionMesh);
    this->mCollider->updatePosition(-worldTransform.getPosition());

    if (!isDynamic()) {
        return;
    }

    this->localTransform.applyPxTransform(pxTransform);

    // note collision mesh for Terrain is the same mesh pointer, will cause some issues
    mCollisionMesh->applyPxTransform(pxTransform);
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
    // setup a collider
    auto collider = new Collider(ColliderConfig{});

    collider->rebuild(this->mRootMesh);
    collider->updateSize();
    glm::vec3 size = collider->getSize();
    float xscale, yscale, zscale;
    xscale = 1 / size.x;


    std::cout << "size "
              << size.x << ","
              << size.y << ","
              << size.z << "\n";
    this->scale({1 / size.x, 1 / size.y, 1 / size.z});
    // get the bounding box
    // needs a collider for that
    // destroy collider
    delete collider;
}

void Model::autoPhysics() {
 // todo: build convex hull - grab all sub mesh vertices
}
