#pragma once

#include "../Component.h"
#include "../Material.h"

class GraphicsAPI;

class MeshData : public Component {
    friend class Collider;

public:
    Material m_material;
    Material m_material_original;
    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec2> m_UVs;
    std::vector<unsigned int> m_indices;
    std::vector<glm::vec3> m_normals;

    std::vector<glm::vec3> m_tangents;
    std::vector<glm::vec3> m_biTangents;

    void addMesh(MeshData *subMesh);

public:
    void addIndex(unsigned int index) {
        this->m_indices.push_back(index);
    }

    void addNormal (glm::vec3 normal){
        this->m_normals.push_back(normal);
    }

    void addVertex (glm::vec3 vertex){
        this->m_vertices.push_back(vertex);
    }

    void addUV( glm::vec2 uv){
        this->m_UVs.push_back(uv);
    }
    MeshData *rootMesh = nullptr;

    std::vector<MeshData *> meshTree;
    /**
     * meshLODTree contains other versions of the meshTree to use, we will need to apply current
     * before switching the pointer we will need to update the transforms of the new LOD meshTree item
     * to that of the current mesh tree.
     */
    std::vector<MeshData *> meshLODTree; // todo allow different meshes to have a different number of LODs,


    void addChild(Component *child) override;

    void setVertices(const std::vector<glm::vec3> &mVertices);

    void setIndices(const std::vector<unsigned int> &mIndices);

    void setUVs(std::vector<glm::vec2> &UVs);

    void setNormals(const std::vector<glm::vec3> &mNormals);

    unsigned int m_gID = 0;
    static GraphicsAPI *m_api;

    ObjectType getType() override {
        return ObjectType::OT_Mesh;
    };

    bool isReady() override;

    MeshData() {
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

    void reduceMeshData(int iterations);
    void reduceMeshData();
    static glm::vec3 calculateMidpoint(const glm::vec3& v1, const glm::vec3& v2);
    static glm::vec2 calculateMidpoint(const glm::vec2& uv1, const glm::vec2& uv2);
    glm::mat4 calculateFaceQEM(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2) ;

    glm::vec3 calculateOptimalPosition(const glm::mat4& qem) ;

    void switchIndexOrder(bool clockwise = true);

    static MeshData * getMeshFromHeightMap(const std::string &filePath, float heightScale, float uvScale, bool flipTriangles = true);
};

