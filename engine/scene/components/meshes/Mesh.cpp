
#include <GraphicsAPI.h>
#include "Mesh.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <unordered_map>
#include <algorithm>

GraphicsAPI *Mesh::m_api;

void Mesh::setApi(GraphicsAPI *api) {
    Mesh::m_api = api;
}

bool Mesh::isReady() {
    if (mReady) return true;

    // not all meshes will need to be rendered, but at the moment only rendering is using readyCheckk
    // we will need to subclass mRootMesh into render and non render types
    if (this->meshData && this->meshData->m_gID != 0) {
        mReady = true;
    }

    return mReady;
}

unsigned int Mesh::generateMeshID() {
    return 0;
}


Material &Mesh::getMaterial() {
    return m_material;
}

void Mesh::setMaterial(const Material &material) {
    // here we need to make a decision about which level of shader to use
    /*
     * Base: simple geometry shader, uses ambient colour to render item, no textures
     * Diffuse: renders diffuse texture with lighting
     * Normal: renders diffuse and normal with lighting
     * PBR: full texture set
     */

    m_material = Mesh::m_material_original = material;
}

unsigned int Mesh::getID() const {
    return this->meshData->m_gID;
}

void Mesh::restoreMaterial() {
    this->m_material = this->m_material_original;
}

void Mesh::applyPxTransform(const physx::PxTransform &pxTransform) {
    this->localTransform.applyPxTransform(pxTransform);
}

void Mesh::addChild(Component *child) {
    if (child->getType() == ObjectType::OT_Mesh) {
        addMesh(dynamic_cast<Mesh *>(child));
    }
    Component::addChild(child);
}

void Mesh::addMesh(Mesh *subMesh) {
    // if this mesh has a parent mesh (is a child), update the mRootMesh tree
    if (this->parentComponent && this->parentComponent->getType() == Object::ObjectType::OT_Mesh) {
        // update existing submesh meshtree parent, root values accordingly
        for (auto nestedMesh: subMesh->meshTree) {
            nestedMesh->parentComponent = this;
            nestedMesh->rootMesh = this->rootMesh;
        }
        rootMesh->meshTree.insert(rootMesh->meshTree.end(), subMesh->meshTree.begin(), subMesh->meshTree.end());

        //todo update all submeshtree items world transform

    } else {
        // if this is the first child being added, make this the mRootMesh
        subMesh->rootMesh = this;
        meshTree.push_back(subMesh);
    }
}

Mesh *Mesh::getMeshFromHeightMap(const std::string &filePath, float heightScale, float uvScale, bool flipTriangles)
{
    //todo check if already exists return existing mesh
    auto mesh = new Mesh();
    mesh->meshData = MeshData::getMeshFromHeightMap(filePath,heightScale,uvScale);
    return mesh;
}

