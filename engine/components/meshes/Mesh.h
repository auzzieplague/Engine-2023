#pragma once

#include "../Component.h"
//#include "../../layers/graphics/api/GraphicsAPI.h"

class GraphicsAPI;

class Mesh : public Component {
    enum TOPOLOGY
    {
        POINTS,
        LINES,
        LINE_STRIP,
        TRIANGLES,
        TRIANGLE_STRIP,
        TRIANGLE_FAN,
    };


    unsigned int topologyID = 0; // updated in initMesh()

public:
    static GraphicsAPI *api;

    static void setApi(GraphicsAPI *api);

    unsigned int gID = 0;
    unsigned int topology = TRIANGLES;

    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> uv;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> tangents;
    std::vector<glm::vec3> bitangents;
    std::vector<unsigned int> indices;

//    static unsigned int (*create_mesh)(Mesh *);

    unsigned int material;
    // todo bounding box

    // just added geometry, adding factory to generate cubes etc,
    // need to pass a test cube through as collision mesh on a model to begin testing
public:

    unsigned int generateMeshID();

    Mesh() {}

    /**
     * load the 3D model data from a file, such as a .obj or .fbx file, into memory.
     * It may also perform any necessary preprocessing, such as calculating normals or tangents.
     */
    void loadMesh(std::string);
//    void loadMesh(assimp);

    /**
     * take the model data and create a mesh object that can be rendered by the engine.
     * The mesh object should contain information such as vertex positions, texture coordinates, and indices.
     */
    void createMesh();

    /**
     * Once the mesh is populated a call to the graphics engine will need to be made to assign the correct, topology
     */
    void initMesh(){
        // assign graphics specific toopology e.g GL trinagles - using api method
        // based on other properties, generate required normalks, materials, MIP maps etc
    };

    /**
     * create a material object that defines how the mesh should be shaded.
     * involve loading textures, setting shader parameters, or defining lighting parameters.
     */
    void createMaterial();

    void calculateNormals() {
        // Initialize the normal vector for each vertex to (0, 0, 0)
        std::vector<glm::vec3> vertexNormals(positions.size(), glm::vec3(0.0f));

        // Iterate over each face of the mesh
        for (size_t i = 0; i < indices.size(); i += 3) {
            // Get the indices of the three vertices that make up the face
            unsigned int i1 = indices[i];
            unsigned int i2 = indices[i + 1];
            unsigned int i3 = indices[i + 2];

            // Calculate the normal vector of the face
            glm::vec3 v1 = positions[i2] - positions[i1];
            glm::vec3 v2 = positions[i3] - positions[i1];
            glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

            // Add the normal vector of the face to the normal vector of each vertex
            vertexNormals[i1] += normal;
            vertexNormals[i2] += normal;
            vertexNormals[i3] += normal;
        }

        // Normalize the normal vector for each vertex
        for (size_t i = 0; i < positions.size(); i++) {
            normals.push_back(glm::normalize(vertexNormals[i]));
        }
    }

    void calculateTangents() {
        // Initialize the tangent and bitangent vectors for each vertex to (0, 0, 0)
        std::vector<glm::vec3> vertexTangents(positions.size(), glm::vec3(0.0f));
        std::vector<glm::vec3> vertexBitangents(positions.size(), glm::vec3(0.0f));

        // Iterate over each face of the mesh
        for (size_t i = 0; i < indices.size(); i += 3) {
            // Get the indices of the three vertices that make up the face
            unsigned int i1 = indices[i];
            unsigned int i2 = indices[i + 1];
            unsigned int i3 = indices[i + 2];

            // Calculate the edge vectors and UV differentials for the face
            glm::vec3 edge1 = positions[i2] - positions[i1];
            glm::vec3 edge2 = positions[i3] - positions[i1];
            glm::vec2 deltaUV1 = uv[i2] - uv[i1];
            glm::vec2 deltaUV2 = uv[i3] - uv[i1];

            // Calculate the determinant of the UV matrix
            float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

            // Calculate the tangent and bitangent vectors for the face
            glm::vec3 tangent(
                    f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x),
                    f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y),
                    f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z)
            );
            glm::vec3 bitangent(
                    f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x),
                    f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y),
                    f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z)
            );

            // Add the tangent and bitangent vectors of the face to the tangent and bitangent vectors of each vertex
            vertexTangents[i1] += tangent;
            vertexTangents[i2] += tangent;
            vertexTangents[i3] += tangent;
            vertexBitangents[i1] += bitangent;
            vertexBitangents[i2] += bitangent;
            vertexBitangents[i3] += bitangent;
        }

        // Calculate the final tangent and bitangent vectors for each vertex
        for (size_t i = 0; i < positions.size(); i++) {
            glm::vec3 normal = normals[i];
            glm::vec3 tangent = vertexTangents[i];

            // Gram-Schmidt orthogonalize the tangent vector with respect to the vertex normal
            tangent = glm::normalize(tangent - normal * glm::dot(normal, tangent));

            // Calculate the handedness of the tangent and bitangent vectors
            float handedness = glm::dot(glm::cross(normal, tangent), vertexBitangents[i]) < 0.0f ? -1.0f : 1.0f;

            // Add the final tangent and bitangent vectors to the mesh
            tangents.emplace_back(glm::vec4(tangent, handedness));
            bitangents.push_back(glm::vec3(vertexBitangents[i] * handedness));
        }
    };

};

