
#include "../../layers/graphics/api/GraphicsAPI.h"
#include "Mesh.h"

GraphicsAPI *Mesh::m_api;

void Mesh::setApi(GraphicsAPI *api) {
    Mesh::m_api = api;
}

bool Mesh::isReady() {
    if (m_ready) return true;

    // not all meshes will need to be rendered, but at the moment only rendering is using readyCheckk
    // we will need to subclass rootMesh into render and non render types
    if (this->m_gID != 0) {
        m_ready = true;
    }

    return m_ready;
}

unsigned int Mesh:: generateMeshID() {
    this->m_gID = m_api->setupMesh(this);
    if (this->m_gID == 0) {
        Debug::show("Failed to generate meshID for " + getName());
    }
    return this->m_gID;
}

void Mesh::calculateNormals() {
    {
        m_normals.clear();
        // Initialize the normal vector for each vertex to (0, 0, 0)
        std::vector<glm::vec3> vertexNormals(m_vertices.size(), glm::vec3(0.0f));

        // Iterate over each face of the rootMesh
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


}

void Mesh::calculateTangents() {
    // Initialize the tangent and bitangent vectors for each vertex to (0, 0, 0)
    std::vector<glm::vec3> vertexTangents(m_vertices.size(), glm::vec3(0.0f));
    std::vector<glm::vec3> vertexBitangents(m_vertices.size(), glm::vec3(0.0f));

    // Iterate over each face of the rootMesh
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

        // Add the final tangent and bitangent vectors to the rootMesh
        m_tangents.emplace_back(glm::vec4(tangent, handedness));
        m_biTangents.push_back(glm::vec3(vertexBitangents[i] * handedness));
    }
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

const std::vector<glm::vec3> &Mesh::getVertices() const {
    return m_vertices;
}

const std::vector<glm::vec2> &Mesh::getUVs() const {
    return m_UVs;
}

const std::vector<glm::vec3> &Mesh::getNormals() const {
    return m_normals;
}

const std::vector<unsigned int> &Mesh::getIndices() const {
    return m_indices;
}

unsigned int Mesh::getID() const {
    return this->m_gID;
}

void Mesh::restoreMaterial() {
    this->m_material = this->m_material_original;
}

void Mesh::applyPxTransform(const physx::PxTransform &pxTransform) {
    this->m_transform.applyPxTransform(pxTransform);
}

void Mesh::setVertices(const std::vector<glm::vec3> &mVertices) {
    m_vertices = mVertices;
}

void Mesh::setIndices(const std::vector<unsigned int> &mIndices) {
    m_indices = mIndices;
}

void Mesh::setUVs(std::vector<glm::vec2> &UVs) {
    m_UVs= UVs;
}

void Mesh::setNormals(const std::vector<glm::vec3> &mNormals) {
    m_normals = mNormals;
}

void Mesh::switchIndexOrder( bool clockwise) {
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
