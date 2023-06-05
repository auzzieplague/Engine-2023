#pragma once

#include "Model.h"
#include "Terrain.h"

Model *Model::createFromGeometry(Geometry::ShapeType shape, GeometryConfig config) {
    auto *model = new Model();
    model->rootMesh = new Geometry();

    std::string shapeText = "";
    switch (shape) {
        default:
            Debug::show("unsupported shape requested by model");
            break;
        case Geometry::ShapeType::Cube :
            shapeText = "Cube";
            dynamic_cast<Geometry *>(model->rootMesh)->buildCube(config);
            break;
        case Geometry::ShapeType::Sphere :
            shapeText = "Sphere";
            dynamic_cast<Geometry *>(model->rootMesh)->buildSphere(config);
            break;
        case Geometry::ShapeType::Terrain :
            shapeText = "Terrain";
            // here we're treating terrain as a model just for testing purposes
            dynamic_cast<Geometry *>(model->rootMesh)->buildTerrain(config);
            break;
        case Geometry::ShapeType::Dome :
            shapeText = "Dome";
            dynamic_cast<Geometry *>(model->rootMesh)->buildDome(config);
            break;
        case Geometry::ShapeType::Torus :
            shapeText = "Torus";
            dynamic_cast<Geometry *>(model->rootMesh)->buildTorus(config);
            break;
        case Geometry::ShapeType::Capsule :
            shapeText = "Capsule";
            dynamic_cast<Geometry *>(model->rootMesh)->buildCapsule(config);
            break;
        case Geometry::ShapeType::Cone :
            shapeText = "Cone";
            dynamic_cast<Geometry *>(model->rootMesh)->buildCone(config);
            break;
        case Geometry::ShapeType::Quad :
            shapeText = "Quad";
            dynamic_cast<Geometry *>(model->rootMesh)->buildQuad(config);
            break;
    }

//    model->rootMesh->calculateNormals();

    // check if model has UVs and Normals, if not, build them
    if (model->rootMesh->getUVs().size() == 0) {
        throw std::runtime_error("missing UVs for shape:" + shapeText);
    }
    if (model->rootMesh->getNormals().size() == 0) {
        throw std::runtime_error("missing Normals for shape:" + shapeText);
    }
    return model;
}

void Model::setPosition(glm::vec3 newPosition) {
    // note: it's a prerequisite that you setCollider() before moving things around
    if (this->mCollider) {
        this->mCollider->updatePosition(m_transform.getPosition() - newPosition);
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
//        this->mCollider->rebuild(rootMesh);
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
        this->mCollider->rebuild(rootMesh);
    }
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
    // note: model would need to be set collidable before adding to scene, to be added to correct <vector>
    mCollider = new Collider(config);
    mCollider->rebuild(rootMesh);
    this->mCollider->updatePosition(-m_transform.getPosition());
    this->mCollider->updateSize(this->getScale());
}

void Model::applyPxTransform(const physx::PxTransform &pxTransform) {

    //todo - will replace isColliding function with physX checks, but until then we will need to apply the position updates to the mCollider
    mCollider->rebuild(rootMesh);
    this->mCollider->updatePosition(-m_transform.getPosition());

    if (!mPhysicsBody) {
        return;
    }
    this->m_transform.applyPxTransform(pxTransform);
}

void Model::getMeshFromHeightMap(std::string name) {
    this->rootMesh = AssetManager::getMeshFromHeightMap(name, 1, 1);
}

physx::PxTransform Model::getPxTransform() {
    return this->m_transform.getPxTransform();
}

void Model::setMaterial(Material material) {
    this->rootMesh->setMaterial(material);
}

void Model::rotateX(float degrees) {
    this->m_transform.rotateX(degrees);
}

void Model::rotateY(float degrees) {
    this->m_transform.rotateY(degrees);
}

void Model::rotateZ(float degrees) {
    this->m_transform.rotateZ(degrees);
}