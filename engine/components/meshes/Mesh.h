#pragma once

#include "../Component.h"
#include "../Material.h"
#include "MeshData.h"

class GraphicsAPI;

class Mesh : public Component {
    friend class Collider;

public:
    Material m_material;
    Material m_material_original;

    MeshData *meshData;

    static GraphicsAPI *m_api;

    ObjectType getType() override {
        return ObjectType::OT_Mesh;
    };

    Mesh *rootMesh = nullptr;
    std::vector<Mesh *> meshTree;
    /**
     * meshLODTree contains other versions of the meshTree to use, we will need to apply current
     * before switching the pointer we will need to update the transforms of the new LOD meshTree item
     * to that of the current mesh tree.
     */
    std::vector<Mesh *> meshLODTree; // todo allow different meshes to have a different number of LODs,

    void addChild(Component *child) override;

    void addMesh(Mesh *subMesh);

    bool isReady() override;

    Mesh() {
        meshTree.push_back(this);
    };

    static void setApi(GraphicsAPI *api);

    void setMaterial(const Material &material);

    void restoreMaterial();

    Material &getMaterial();

    [[nodiscard]] unsigned int getID() const;

    /**
     * Note: not all meshes will require loading into video ram,
     * some meshes are only for collision. Some meshes, although in proximity to the view may never be seen,
     * so we will only generateMeshID when attempting to render an object that doesnt already have one.
     * @return
     */
    unsigned int generateMeshID();

    void applyPxTransform(const physx::PxTransform &pxTransform);

    static Mesh *getMeshFromHeightMap(const std::string &filePath, float heightScale, float uvScale, bool flipTriangles = true);
};

