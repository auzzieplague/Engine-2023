
#include "../../layers/graphics/api/GraphicsAPI.h"
#include "MeshData.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <unordered_map>
#include <algorithm>


GraphicsAPI *MeshData::m_api;

void MeshData::setApi(GraphicsAPI *api) {
    MeshData::m_api = api;
}

void MeshData::setVertices(const std::vector<glm::vec3> &mVertices) {
    m_vertices = mVertices;
}

void MeshData::setIndices(const std::vector<unsigned int> &mIndices) {
    m_indices = mIndices;
}

void MeshData::setUVs(std::vector<glm::vec2> &UVs) {
    m_UVs = UVs;
}

void MeshData::setNormals(const std::vector<glm::vec3> &mNormals) {
    m_normals = mNormals;
}

void MeshData::switchIndexOrder(bool clockwise) {
    if (clockwise) {
        for (size_t i = 0; i < m_indices.size(); i += 3) {
            std::swap(m_indices[i], m_indices[i + 1]);
        }
    } else {
        for (size_t i = 0; i < m_indices.size(); i += 3) {
            std::swap(m_indices[i], m_indices[i + 2]);
        }
    }
}


const std::vector<glm::vec3> &MeshData::getVertices() const {
    return m_vertices;
}

const std::vector<glm::vec2> &MeshData::getUVs() const {
    return m_UVs;
}

const std::vector<glm::vec3> &MeshData::getNormals() const {
    return m_normals;
}

const std::vector<unsigned int> &MeshData::getIndices() const {
    return m_indices;
}


void MeshData::calculateTangents() {
    // Initialize the tangent and bitangent vectors for each vertex to (0, 0, 0)
    std::vector<glm::vec3> vertexTangents(m_vertices.size(), glm::vec3(0.0f));
    std::vector<glm::vec3> vertexBitangents(m_vertices.size(), glm::vec3(0.0f));

    // Iterate over each face of the mRootMesh
    for (size_t i = 0; i < m_indices.size(); i += 3) {
        // Get the m_indices of the three m_vertices that make m_up the face
        unsigned int i1 = m_indices[i];
        unsigned int i2 = m_indices[i + 1];
        unsigned int i3 = m_indices[i + 2];

        // Calculate the edge vectors and UV differentials for the face
        glm::vec3 edge1 = m_vertices[i2] - m_vertices[i1];
        glm::vec3 edge2 = m_vertices[i3] - m_vertices[i1];
        glm::vec2 deltaUV1 = m_UVs[i2] - m_UVs[i1];
        glm::vec2 deltaUV2 = m_UVs[i3] - m_UVs[i1];

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
    for (size_t i = 0; i < m_vertices.size(); i++) {
        glm::vec3 normal = m_normals[i];
        glm::vec3 tangent = vertexTangents[i];

        // Gram-Schmidt orthogonalize the tangent vector with respect to the vertex normal
        tangent = glm::normalize(tangent - normal * glm::dot(normal, tangent));

        // Calculate the handedness of the tangent and bitangent vectors
        float handedness = glm::dot(glm::cross(normal, tangent), vertexBitangents[i]) < 0.0f ? -1.0f : 1.0f;

        // Add the final tangent and bitangent vectors to the mRootMesh
        m_tangents.emplace_back(glm::vec4(tangent, handedness));
        m_biTangents.push_back(glm::vec3(vertexBitangents[i] * handedness));
    }
}


void MeshData::calculateNormals() {
    m_normals.clear();
    // Initialize the normal vector for each vertex to (0, 0, 0)
    std::vector<glm::vec3> vertexNormals(m_vertices.size(), glm::vec3(0.0f));

    // Iterate over each face of the mRootMesh
    for (size_t i = 0; i < m_indices.size(); i += 3) {
        // Get the m_indices of the three m_vertices that make m_up the face
        unsigned int i1 = m_indices[i];
        unsigned int i2 = m_indices[i + 1];
        unsigned int i3 = m_indices[i + 2];

        // Calculate the normal vector of the face
        glm::vec3 v1 = m_vertices[i2] - m_vertices[i1];
        glm::vec3 v2 = m_vertices[i3] - m_vertices[i1];
        glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

        // Add the normal vector of the face to the normal vector of each vertex
        vertexNormals[i1] += normal;
        vertexNormals[i2] += normal;
        vertexNormals[i3] += normal;
    }

    // Normalize the normal vector for each vertex
    for (size_t i = 0; i < m_vertices.size(); i++) {
        m_normals.push_back(glm::normalize(vertexNormals[i]));
    }

}


void MeshData::reduceMeshData(int iterations) {
    for (int i = 0; i < iterations; i++) {
        this->reduceMeshData();
    }
}

void MeshData::reduceMeshData() {
    int reductionRatio = 2;
    // Compute the number of target faces based on the reduction ratio
    size_t targetFaces = static_cast<size_t>(m_indices.size() * reductionRatio);

    // Create a map to track vertex usage count
    std::unordered_map<unsigned int, size_t> vertexUsage;

    // Iterate over each face and count vertex usage
    for (size_t i = 0; i < m_indices.size(); i += 3) {
        unsigned int v0 = m_indices[i];
        unsigned int v1 = m_indices[i + 1];
        unsigned int v2 = m_indices[i + 2];

        vertexUsage[v0]++;
        vertexUsage[v1]++;
        vertexUsage[v2]++;
    }

    // Create a copy of the original vertices and UVs
    std::vector<glm::vec3> reducedVertices = m_vertices;
    std::vector<glm::vec2> reducedUVs = m_UVs;

    // Sort the vertices based on usage count (from least used to most used)
//    std::sort(reducedVertices.begin(), reducedVertices.end(), [&](const glm::vec3& v1, const glm::vec3& v2) {
//        return vertexUsage[v1] < vertexUsage[v2];
//    });

    // Resize the vertices and UVs based on the target number of faces
    reducedVertices.resize(targetFaces * 3);
    reducedUVs.resize(targetFaces * 3);

    // Create a mapping between original and reduced vertex m_indices
    std::unordered_map<unsigned int, unsigned int> vertexMap;
    unsigned int nextIndex = 0;

    // Update the m_indices based on the reduced vertices
    for (size_t i = 0; i < m_indices.size(); i += 3) {
        unsigned int v0 = m_indices[i];
        unsigned int v1 = m_indices[i + 1];
        unsigned int v2 = m_indices[i + 2];

        if (vertexMap.find(v0) == vertexMap.end()) {
            vertexMap[v0] = nextIndex;
            reducedVertices[nextIndex] = m_vertices[v0];
            reducedUVs[nextIndex] = m_UVs[v0];
            nextIndex++;
        }

        if (vertexMap.find(v1) == vertexMap.end()) {
            vertexMap[v1] = nextIndex;
            reducedVertices[nextIndex] = m_vertices[v1];
            reducedUVs[nextIndex] = m_UVs[v1];
            nextIndex++;
        }

        if (vertexMap.find(v2) == vertexMap.end()) {
            vertexMap[v2] = nextIndex;
            reducedVertices[nextIndex] = m_vertices[v2];
            reducedUVs[nextIndex] = m_UVs[v2];
            nextIndex++;
        }

        m_indices[i] = vertexMap[v0];
        m_indices[i + 1] = vertexMap[v1];
        m_indices[i + 2] = vertexMap[v2];
    }

    // Update the original vertex and UV arrays with the reduced data
    m_vertices = reducedVertices;
    m_UVs = reducedUVs;
}

glm::vec3 MeshData::calculateMidpoint(const glm::vec3 &v1, const glm::vec3 &v2) {
    return (v1 + v2) * 0.5f;
}

glm::vec2 MeshData::calculateMidpoint(const glm::vec2 &uv1, const glm::vec2 &uv2) {
    return (uv1 + uv2) * 0.5f;
}

glm::mat4 MeshData::calculateFaceQEM(const glm::vec3 &v0, const glm::vec3 &v1, const glm::vec3 &v2) {
    glm::vec3 n = glm::normalize(glm::cross(v1 - v0, v2 - v0));
    glm::vec4 plane(n, -glm::dot(n, v0));
    glm::mat4 qem = glm::outerProduct(plane, plane);
    return qem;
}

glm::vec3 MeshData::calculateOptimalPosition(const glm::mat4 &qem) {
    // Compute the optimal position as the minimum eigenvector of the QEM matrix
    glm::mat3 qem3 = glm::mat3(qem);
    glm::mat3 invQEM3 = glm::inverse(qem3);
    glm::vec3 optimalPosition = -glm::vec3(invQEM3[0][2], invQEM3[1][2], invQEM3[2][2]) / invQEM3[2][2];
    return optimalPosition;
}

MeshData * MeshData::getMeshFromHeightMap(const std::string &fileName, float heightScale, float uvScale, bool flipTriangles) {

    auto filename = AssetManager::getRelativePath("heightmap", fileName + ".png");
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &channels, 1);

    if (!data) {
        std::cerr << "Failed to load height map " << filename << std::endl;
        return nullptr;
    }

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uv;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;

    // Calculate center offset
    glm::vec3 offset(-0.5f * static_cast<float>(width) / static_cast<float>(height), 0.0f, -0.5f);

    // Generate vertices and UVs
    for (int z = 0; z < height; z++) {
        for (int x = 0; x < width; x++) {
            float xPos = (float) x / (float) width;
            float zPos = (float) z / (float) height;
            float yPos = ((float) data[z * width + x] / 255.0f) * heightScale;
            // Center the mesh at (0, 0, 0)
            glm::vec3 vertexPos(xPos, yPos, zPos);
            vertexPos += offset;
            vertices.push_back(vertexPos);
            uv.emplace_back(xPos * uvScale, zPos * uvScale);
        }
    }

    // Generate indices
    for (int z = 0; z < height - 1; z++) {
        for (int x = 0; x < width - 1; x++) {
            int topLeft = (z * width) + x;
            int topRight = topLeft + 1;
            int bottomLeft = ((z + 1) * width) + x;
            int bottomRight = bottomLeft + 1;

            if (flipTriangles) {
                indices.push_back(topLeft);
                indices.push_back(bottomLeft);
                indices.push_back(topRight);
                indices.push_back(topRight);
                indices.push_back(bottomLeft);
                indices.push_back(bottomRight);
            } else {
                indices.push_back(bottomLeft);
                indices.push_back(topLeft);
                indices.push_back(topRight);
                indices.push_back(bottomRight);
                indices.push_back(bottomLeft);
                indices.push_back(topRight);
            }

        }
    }

    // Generate normals
    for (unsigned int i = 0; i < indices.size(); i += 3) {
        glm::vec3 v0 = vertices[indices[i + 0]];
        glm::vec3 v1 = vertices[indices[i + 1]];
        glm::vec3 v2 = vertices[indices[i + 2]];

        glm::vec3 e1 = v1 - v0;
        glm::vec3 e2 = v2 - v0;
        glm::vec3 normal = glm::normalize(glm::cross(e1, e2));

        normals.push_back(normal);
        normals.push_back(normal);
        normals.push_back(normal);
    }

    // Generate tangents and bitangents
    for (unsigned int i = 0; i < indices.size(); i += 3) {
        glm::vec3 v0 = vertices[indices[i + 0]];
        glm::vec3 v1 = vertices[indices[i + 1]];
        glm::vec3 v2 = vertices[indices[i + 2]];

        glm::vec2 uv0 = uv[indices[i + 0]];
        glm::vec2 uv1 = uv[indices[i + 1]];
        glm::vec2 uv2 = uv[indices[i + 2]];

        glm::vec3 deltaPos1 = v1 - v0;
        glm::vec3 deltaPos2 = v2 - v0;

        glm::vec2 deltaUV1 = uv1 - uv0;
        glm::vec2 deltaUV2 = uv2 - uv0;

        float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

//        glm::vec3 tangent;
//        tangent.x = f * (deltaUV2.y * deltaPos1.x - deltaUV1.y * deltaPos2.x);
//        tangent.y = f * (deltaUV2.y * deltaPos1.y - deltaUV1.y * deltaPos2.y);
//        tangent.z = f * (deltaUV2.y * deltaPos1.z - deltaUV1.y * deltaPos2.z);
//        tangent = glm::normalize(tangent);
//
//        glm::vec3 bitangent;
//        bitangent.x = f * (-deltaUV2.x * deltaPos1.x + deltaUV1.x * deltaPos2.x);
//        bitangent.y = f * (-deltaUV2.x * deltaPos1.y + deltaUV1.x * deltaPos2.y);
//        bitangent.z = f * (-deltaUV2.x * deltaPos1.z + deltaUV1.x * deltaPos2.z);
//        bitangent = glm::normalize(bitangent);
//
//        // Assign tangent and bitangent to each vertex of the triangle
//        m_tangents.push_back(tangent);
//        m_tangents.push_back(tangent);
//        m_tangents.push_back(tangent);
//
//        m_biTangents.push_back(bitangent);
//        m_biTangents.push_back(bitangent);
//        m_biTangents.push_back(bitangent);
    }

// Release memory allocated for image data
    stbi_image_free(data);

// Create and return the mesh object
    MeshData *mesh = new MeshData();
    mesh->setVertices(vertices);
    mesh->setIndices(indices);
    mesh->setUVs(uv);
    mesh->setNormals(normals);
//    mesh->setTangents(m_tangents);
//    mesh->setBiTangents(m_biTangents);
    return mesh;
}