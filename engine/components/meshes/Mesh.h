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
    std::vector<glm::vec2> m_uv;
    std::vector<glm::vec3> m_normals;
    std::vector<glm::vec3> m_tangents;
    std::vector<glm::vec3> m_biTangents;
    std::vector<unsigned int> m_indices;

    unsigned int m_topology = TRIANGLES;
    unsigned int m_topologyID = 0; // updated in initMesh()
    unsigned int m_gID = 0;
    static GraphicsAPI *m_api;

public:
    enum TOPOLOGY {
        POINTS,
        LINES,
        LINE_STRIP,
        TRIANGLES,
        TRIANGLE_STRIP,
        TRIANGLE_FAN,
    };

    ObjectType getType() override {
        return ObjectType::OT_Mesh;
    };

    std::string getName() override {
        return "Mesh - name tbc";
    };

    bool isReady() override;

    Mesh() = default;

    static void setApi(GraphicsAPI *api);

    void setMaterial(const Material &material);
    void restoreMaterial();

    Material &getMaterial();

    [[nodiscard]] const std::vector<glm::vec3> &getVertices() const;

    [[nodiscard]] const std::vector<glm::vec2> &getUv() const;

    [[nodiscard]] const std::vector<glm::vec3> &getNormals() const;

    [[nodiscard]] const std::vector<glm::vec3> &getTangents() const;

    [[nodiscard]] const std::vector<glm::vec3> &getBiTangents() const;

    [[nodiscard]] const std::vector<unsigned int> &getIndices() const;

    unsigned int getID();

    /**
     * Note: not all meshes will require loading into video ram,
     * some meshes are only for collision. Some meshes, although in proximity to the view may never be seen,
     * so we will only generateMeshID when attempting to render an object that doesnt already have one.
     * @return
     */
    unsigned int generateMeshID();

    void calculateNormals();

    void calculateTangents();

};

