#pragma once
#include "Component.h"

class MeshData
    : public Component {
    friend class Mesh;
public:
    unsigned int m_gID = 0;
    static GraphicsAPI *m_api;

    ObjectType getType() override {
        return ObjectType::OT_MeshData;
    };

    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec2> m_UVs;
    std::vector<unsigned int> m_indices;
    std::vector<glm::vec3> m_normals;

    std::vector<glm::vec3> m_tangents;
    std::vector<glm::vec3> m_biTangents;

public:
    static void setApi(GraphicsAPI *api);

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

    void setVertices(const std::vector<glm::vec3> &mVertices);

    void setIndices(const std::vector<unsigned int> &mIndices);

    void setUVs(std::vector<glm::vec2> &UVs);

    void setNormals(const std::vector<glm::vec3> &mNormals);

    static MeshData * getMeshFromHeightMap(const std::string &filePath, float heightScale, float uvScale, bool flipTriangles = true);

    [[nodiscard]] const std::vector<glm::vec3> &getVertices() const;

    [[nodiscard]] const std::vector<glm::vec2> &getUVs() const;

    [[nodiscard]] const std::vector<glm::vec3> &getNormals() const;

    [[nodiscard]] const std::vector<unsigned int> &getIndices() const;

    void calculateNormals();
    void calculateTangents();

    void reduceMeshData(int iterations);
    void reduceMeshData();
    static glm::vec3 calculateMidpoint(const glm::vec3& v1, const glm::vec3& v2);
    static glm::vec2 calculateMidpoint(const glm::vec2& uv1, const glm::vec2& uv2);
    glm::mat4 calculateFaceQEM(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2) ;
    glm::vec3 calculateOptimalPosition(const glm::mat4& qem) ;

    void switchIndexOrder(bool clockwise = true);

};

