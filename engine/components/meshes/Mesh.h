#pragma once

#include "../Component.h"
#include "../Material.h"
//#include "../../layers/graphics/m_api/GraphicsAPI.h"

class GraphicsAPI;

class Mesh : public Component {
public:
    enum TOPOLOGY
    {
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

    unsigned int topology = TRIANGLES;
    unsigned int topologyID = 0; // updated in initMesh()
    unsigned int gID = 0;

    Material material;
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> uv;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> tangents;
    std::vector<glm::vec3> bitangents;
    std::vector<unsigned int> indices;

    static GraphicsAPI *api;

    Mesh() = default;
    static void setApi(GraphicsAPI *api);
    bool isReady() override;

    /**
     * Note: not all meshes will require loading into video ram,
     * some meshes are only for collision. Some meshes, although in proximity to the view may never be seen,
     * so we will only generateMeshID when attempting to render an object that doesnt already have one.
     * @return
     */
    unsigned int generateMeshID();

    void calculateNormals() ;
    void calculateTangents() ;

};

