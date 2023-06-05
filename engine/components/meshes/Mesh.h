#pragma once

#include "../Component.h"
#include "../Material.h"

class GraphicsAPI;

class Mesh : public Component {
    friend class Collider;

protected:
    Material m_material;
    Material m_material_original;
    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec2> m_UVs;
    std::vector<glm::vec3> m_normals;
    std::vector<unsigned int> m_indices;

    std::vector<glm::vec3> m_tangents;
    std::vector<glm::vec3> m_biTangents;

public:
    enum TOPOLOGY {
        POINTS,
        LINES,
        LINE_STRIP,
        TRIANGLES,
        TRIANGLE_STRIP,
        TRIANGLE_FAN,
    };

    Mesh *parentMesh = nullptr;
    Mesh *rootMesh = nullptr;
//    std::vector<Mesh *> subMeshes;
    std::vector<Mesh *> meshTree;

    void addMesh(Mesh *subMesh) {
        subMesh->parentMesh = this;
//        subMeshes.push_back(subMesh);
        childComponents.push_back(subMesh);
        // each mesh should know its parent and root, and be added to the root mesh tree

        if (this->parentMesh) {
            // all children should be added to the root node
            rootMesh->meshTree.push_back(subMesh);
        } else {
            // if this is the first child being added, assign rootMesh
            subMesh->rootMesh = this;
            meshTree.push_back(subMesh);
        }
    };

    void setVertices(const std::vector<glm::vec3> &mVertices);

    void setIndices(const std::vector<unsigned int> &mIndices);

    void setUVs(std::vector<glm::vec2> &UVs);

    void setNormals(const std::vector<glm::vec3> &mNormals);

    TOPOLOGY m_topology = TRIANGLES;
    unsigned int m_topologyID = 0; // updated in initMesh()
    unsigned int m_gID = 0;
    static GraphicsAPI *m_api;

    ObjectType getType() override {
        return ObjectType::OT_Mesh;
    };

    std::string getName() override {
        return "Mesh - name tbc";
    };

    bool isReady() override;

    Mesh() {
        meshTree.push_back(this);
    };

    static void setApi(GraphicsAPI *api);

    void setMaterial(const Material &material);

    void restoreMaterial();

    Material &getMaterial();

    [[nodiscard]] const std::vector<glm::vec3> &getVertices() const;

    [[nodiscard]] const std::vector<glm::vec2> &getUVs() const;

    [[nodiscard]] const std::vector<glm::vec3> &getNormals() const;

    [[nodiscard]] const std::vector<glm::vec3> &getTangents() const;

    [[nodiscard]] const std::vector<glm::vec3> &getBiTangents() const;

    [[nodiscard]] const std::vector<unsigned int> &getIndices() const;

    [[nodiscard]] unsigned int getID() const;

    /**
     * Note: not all meshes will require loading into video ram,
     * some meshes are only for collision. Some meshes, although in proximity to the view may never be seen,
     * so we will only generateMeshID when attempting to render an object that doesnt already have one.
     * @return
     */
    unsigned int generateMeshID();

    void calculateNormals();

    void calculateTangents();

    void applyPxTransform(const physx::PxTransform &pxTransform);

    void switchIndexOrder(bool clockwise = true);
};

