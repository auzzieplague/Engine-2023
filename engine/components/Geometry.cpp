#pragma once

#include "Geometry.h"

void Geometry::buildQuad(GeometryConfig config) {
    // Define the vertex m_vertices
    std::vector<glm::vec3> vertices = {
            glm::vec3(-config.quad.sizeX, config.quad.sizeY, 0.0f),
            glm::vec3(config.quad.sizeX, config.quad.sizeY, 0.0f),
            glm::vec3(config.quad.sizeX, -config.quad.sizeY, 0.0f),
            glm::vec3(-config.quad.sizeX, -config.quad.sizeY, 0.0f)
    };

    // Define the m_indices of the two triangles that make m_up the quad
    std::vector<unsigned int> indices = {
            0, 1, 2,
            2, 3, 0
    };

    // Define the UVs
    std::vector<glm::vec2> uvs = {
            glm::vec2(0.0f, 1.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(0.0f, 0.0f)
    };

    // Define the normals
    std::vector<glm::vec3> normals = {
            glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec3(0.0f, 0.0f, 1.0f)
    };

    // Assign the vertex m_vertices and m_indices to the mRootMesh
    this->meshData->setVertices(vertices);
    this->meshData->setIndices(indices);
    this->meshData->setNormals(normals);
    this->meshData->setUVs(uvs);
}

void Geometry::buildCube(GeometryConfig config) {
    config.box.sizeX = config.box.sizeY = config.box.sizeZ = config.cube.size;
    buildBox(config);
}

void Geometry::buildBox(GeometryConfig config) {
    std::vector<glm::vec3> vertices = {
            // Front face
            glm::vec3(-config.box.sizeX, -config.box.sizeY, config.box.sizeZ),
            glm::vec3(config.box.sizeX, -config.box.sizeY, config.box.sizeZ),
            glm::vec3(config.box.sizeX, config.box.sizeY, config.box.sizeZ),
            glm::vec3(-config.box.sizeX, config.box.sizeY, config.box.sizeZ),
            // Back face
            glm::vec3(config.box.sizeX, -config.box.sizeY, -config.box.sizeZ),
            glm::vec3(-config.box.sizeX, -config.box.sizeY, -config.box.sizeZ),
            glm::vec3(-config.box.sizeX, config.box.sizeY, -config.box.sizeZ),
            glm::vec3(config.box.sizeX, config.box.sizeY, -config.box.sizeZ),
            // Top face
            glm::vec3(-config.box.sizeX, config.box.sizeY, config.box.sizeZ),
            glm::vec3(config.box.sizeX, config.box.sizeY, config.box.sizeZ),
            glm::vec3(config.box.sizeX, config.box.sizeY, -config.box.sizeZ),
            glm::vec3(-config.box.sizeX, config.box.sizeY, -config.box.sizeZ),
            // Bottom face
            glm::vec3(-config.box.sizeX, -config.box.sizeY, -config.box.sizeZ),
            glm::vec3(config.box.sizeX, -config.box.sizeY, -config.box.sizeZ),
            glm::vec3(config.box.sizeX, -config.box.sizeY, config.box.sizeZ),
            glm::vec3(-config.box.sizeX, -config.box.sizeY, config.box.sizeZ),
            // Right face
            glm::vec3(config.box.sizeX, -config.box.sizeY, config.box.sizeZ),
            glm::vec3(config.box.sizeX, -config.box.sizeY, -config.box.sizeZ),
            glm::vec3(config.box.sizeX, config.box.sizeY, -config.box.sizeZ),
            glm::vec3(config.box.sizeX, config.box.sizeY, config.box.sizeZ),
            // Left face
            glm::vec3(-config.box.sizeX, -config.box.sizeY, -config.box.sizeZ),
            glm::vec3(-config.box.sizeX, -config.box.sizeY, config.box.sizeZ),
            glm::vec3(-config.box.sizeX, config.box.sizeY, config.box.sizeZ),
            glm::vec3(-config.box.sizeX, config.box.sizeY, -config.box.sizeZ),
    };

    std::vector<unsigned int> indices = {
            // Front face
            0, 1, 2,
            2, 3, 0,
            // Back face
            4, 5, 6,
            6, 7, 4,
            // Top face
            8, 9, 10,
            10, 11, 8,
            // Bottom face
            12, 13, 14,
            14, 15, 12,
            // Right face
            16, 17, 18,
            18, 19, 16,
            // Left face
            20, 21, 22,
            22, 23, 20
    };

    std::vector<glm::vec2> uvs = {
            // Front face
            glm::vec2(0.0f, 0.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(0.0f, 1.0f),
            // Back face
            glm::vec2(0.0f, 0.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(0.0f, 1.0f),
            // Top face
            glm::vec2(0.0f, 1.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(0.0f, 0.0f),
            // Bottom face
            glm::vec2(0.0f, 0.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(0.0f, 1.0f),
            // Right face
            glm::vec2(0.0f, 0.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(0.0f, 1.0f),
            // Left face
            glm::vec2(0.0f, 0.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(0.0f, 1.0f),
    };

    std::vector<glm::vec3> normals = {
            // Front face
            glm::vec3(0.0f, 0.0f, -1.0f),
            glm::vec3(0.0f, 0.0f, -1.0f),
            glm::vec3(0.0f, 0.0f, -1.0f),
            glm::vec3(0.0f, 0.0f, -1.0f),
            // Back face
            glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec3(0.0f, 0.0f, 1.0f),
            // Top face
            glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f),
            // Bottom face
            glm::vec3(0.0f, -1.0f, 0.0f),
            glm::vec3(0.0f, -1.0f, 0.0f),
            glm::vec3(0.0f, -1.0f, 0.0f),
            glm::vec3(0.0f, -1.0f, 0.0f),
            // Right face
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 0.0f, 0.0f),
            // Left face
            glm::vec3(-1.0f, 0.0f, 0.0f),
            glm::vec3(-1.0f, 0.0f, 0.0f),
            glm::vec3(-1.0f, 0.0f, 0.0f),
            glm::vec3(-1.0f, 0.0f, 0.0f),
    };

    // Assign the vertex m_vertices and m_indices to the mRootMesh
    this->meshData->setVertices(vertices);
    this->meshData->setIndices(indices);
    this->meshData->setNormals(normals);
    this->meshData->setUVs(uvs);
}

void Geometry::buildDome(GeometryConfig config) {
    this->meshData->m_vertices.clear();
    this->meshData->m_indices.clear();

    // Generate the vertex m_vertices
    for (unsigned int j = 0; j <= config.dome.segments; j++) {
        float y = cos(-pi / 2.0f + (float) j / (float) config.dome.segments * pi);
        float r = sin(-pi / 2.0f + (float) j / (float) config.dome.segments * pi) * config.dome.radius;

        for (unsigned int i = 0; i <= config.dome.segments; i++) {
            float x = cos((float) i / (float) config.dome.segments * 2.0f * pi) * r;
            float z = sin((float) i / (float) config.dome.segments * 2.0f * pi) * r;

            this->meshData->m_vertices.emplace_back(x, y, z);
        }
    }

    // Generate the triangle m_indices
    for (unsigned int j = 0; j < config.dome.segments; j++) {
        for (unsigned int i = 0; i < config.dome.segments; i++) {
            unsigned int a = j * (config.dome.segments + 1) + i;
            unsigned int b = a + 1;
            unsigned int c = (j + 1) * (config.dome.segments + 1) + i;
            unsigned int d = c + 1;

            this->meshData->m_indices.push_back(a);
            this->meshData->m_indices.push_back(b);
            this->meshData->m_indices.push_back(d);

            this->meshData->m_indices.push_back(a);
            this->meshData->m_indices.push_back(d);
            this->meshData->m_indices.push_back(c);
        }
    }
}

void Geometry::buildSphere(GeometryConfig config) {
    float const R = 1.0f / (float) (config.sphere.rings - 1);
    float const S = 1.0f / (float) (config.sphere.sectors - 1);
    float phi, theta;

    this->meshData->m_vertices.clear();
    this->meshData->m_indices.clear();
    for (unsigned int r = 0; r < config.sphere.rings; ++r) {
        for (unsigned int s = 0; s < config.sphere.sectors; ++s) {
            phi = pi * r * R;
            theta = 2.0f * pi * s * S;
            float x = sin(phi) * cos(theta);
            float y = cos(phi);
            float z = sin(phi) * sin(theta);
            glm::vec3 position = glm::vec3(x, y, z) * config.sphere.radius;

            // Calculate UV coordinates
            float u = static_cast<float>(s) / (config.sphere.sectors - 1);
            float v = static_cast<float>(r) / (config.sphere.rings - 1);

            // Calculate normals
            glm::vec3 normal = glm::normalize(position);

            this->meshData->m_vertices.push_back(position);
            this->meshData->m_UVs.push_back(glm::vec2(u, v));
            this->meshData->m_normals.push_back(normal);
        }
    }

    for (unsigned int r = 0; r < config.sphere.rings - 1; ++r) {
        for (unsigned int s = 0; s < config.sphere.sectors - 1; ++s) {
            unsigned int idx = r * config.sphere.sectors + s;
            this->meshData->m_indices.push_back(idx);
            this->meshData->m_indices.push_back(idx + 1);
            this->meshData->m_indices.push_back((r + 1) * config.sphere.sectors + s + 1);
            this->meshData->m_indices.push_back((r + 1) * config.sphere.sectors + s + 1);
            this->meshData->m_indices.push_back((r + 1) * config.sphere.sectors + s);
            this->meshData->m_indices.push_back(idx);
        }
    }
}
//
//void Geometry::buildSphere(GeometryConfig config) {
//    float const R = 1.0f / (float) (config.sphere.rings - 1);
//    float const S = 1.0f / (float) (config.sphere.sectors - 1);
//    float phi, theta;
//
//    m_vertices.clear();
//    m_indices.clear();
//    for (unsigned int r = 0; r < config.sphere.rings; ++r) {
//        for (unsigned int s = 0; s < config.sphere.sectors; ++s) {
//            phi = pi * r * R;
//            theta = 2.0f * pi * s * S;
//            float x = sin(phi) * cos(theta);
//            float y = cos(phi);
//            float z = sin(phi) * sin(theta);
//            m_vertices.push_back(glm::vec3(x, y, z) * config.sphere.radius);
//        }
//    }
//
//    for (unsigned int r = 0; r < config.sphere.rings - 1; ++r) {
//        for (unsigned int s = 0; s < config.sphere.sectors - 1; ++s) {
//            unsigned int idx = r * config.sphere.sectors + s;
//            m_indices.push_back(idx);
//            m_indices.push_back(idx + 1);
//            m_indices.push_back((r + 1) * config.sphere.sectors + s + 1);
//            m_indices.push_back((r + 1) * config.sphere.sectors + s + 1);
//            m_indices.push_back((r + 1) * config.sphere.sectors + s);
//            m_indices.push_back(idx);
//        }
//    }
//}

void Geometry::buildCapsule(GeometryConfig config) {
    float segmentAngle = pi2 / config.capsule.segments;

    // Create top hemisphere
    for (unsigned int j = 0; j <= config.capsule.segments / 4; j++) {
        float inclination = segmentAngle * j;
        float z = config.capsule.radius * cos(inclination) + config.capsule.halfLength - config.capsule.radius;
        float xy = config.capsule.radius * sin(inclination);
        for (unsigned int i = 0; i <= config.capsule.segments; i++) {
            float azimuth = segmentAngle * i;
            float x = xy * cos(azimuth);
            float y = xy * sin(azimuth);
            this->meshData->m_vertices.push_back(glm::vec3(x, y, z));
        }
    }

    // Create bottom hemisphere
    for (unsigned int j = 3 * config.capsule.segments / 4; j <= config.capsule.segments; j++) {
        float inclination = segmentAngle * j;
        float z = config.capsule.radius * cos(inclination) - config.capsule.halfLength + config.capsule.radius;
        float xy = config.capsule.radius * sin(inclination);
        for (unsigned int i = 0; i <= config.capsule.segments; i++) {
            float azimuth = segmentAngle * i;
            float x = xy * cos(azimuth);
            float y = xy * sin(azimuth);
            this->meshData->m_vertices.push_back(glm::vec3(x, y, z));
        }
    }

    // Create cylinder
    unsigned int topStart = 0;
    unsigned int bottomStart = this->meshData->m_vertices.size() - (config.capsule.segments + 1);
    for (unsigned int j = 0; j < config.capsule.segments; j++) {
        unsigned int offset = j * (config.capsule.segments + 1);
        for (unsigned int i = 0; i < config.capsule.segments; i++) {
            this->meshData->m_indices.push_back(topStart + offset + i);
            this->meshData->m_indices.push_back(topStart + offset + i + 1);
            this->meshData->m_indices.push_back(bottomStart + offset + i);

            this->meshData->m_indices.push_back(bottomStart + offset + i);
            this->meshData->m_indices.push_back(topStart + offset + i + 1);
            this->meshData->m_indices.push_back(bottomStart + offset + i + 1);
        }
    }
}

/// torus has index glitch
void Geometry::buildTorus(GeometryConfig config) {
    this->meshData->m_vertices.clear();
    this->meshData->m_indices.clear();

    float segmentAngle = pi2 / config.torus.segments;
    float sideAngle = pi2 / config.torus.sides;

    // Compute torus m_vertices
    for (int i = 0; i <= config.torus.segments; i++) {
        float phi = i * segmentAngle;
        glm::vec3 center(std::cos(phi), std::sin(phi), 0.0f);

        for (int j = 0; j <= config.torus.sides; j++) {
            float theta = j * sideAngle;
            glm::vec3 dir(std::cos(theta), std::sin(theta), 0.0f);
            glm::vec3 vertex = center * (config.torus.radius + config.torus.tubeRadius * std::cos(theta)) +
                               dir * config.torus.tubeRadius * std::sin(theta);
            this->meshData->m_vertices.push_back(vertex);
        }
    }

    // Compute torus m_indices
    for (int i = 0; i < config.torus.segments; i++) {
        int k1 = i * (config.torus.sides + 1);
        int k2 = k1 + config.torus.sides + 1;

        for (int j = 0; j < config.torus.sides; j++, k1++, k2++) {
            if (j == config.torus.sides - 1) {
                this->meshData->m_indices.push_back(k1);
                this->meshData->m_indices.push_back(k2);
                this->meshData->m_indices.push_back(
                        i == config.torus.segments - 1 ? k2 - config.torus.sides - 1 : k1 - config.torus.sides - 1);

                this->meshData->m_indices.push_back(
                        i == config.torus.segments - 1 ? k2 - config.torus.sides - 1 : k1 - config.torus.sides - 1);
                this->meshData->m_indices.push_back(k2);
                this->meshData->m_indices.push_back(i == config.torus.segments - 1 ? k1 : k2);
            } else {
                this->meshData->m_indices.push_back(k1);
                this->meshData->m_indices.push_back(k2);
                this->meshData->m_indices.push_back(k1 + 1);

                this->meshData->m_indices.push_back(k1 + 1);
                this->meshData->m_indices.push_back(k2);
                this->meshData->m_indices.push_back(k2 + 1);
            }
        }
    }
}

void Geometry::buildCone(GeometryConfig config) {

    // Calculate vertex and index counts
    int vertexCount = config.cone.segments * 2 + 2;
    int indexCount = config.cone.segments * 6;

    // Resize vectors to hold new data
    this->meshData->m_indices.resize(indexCount);
    this->meshData->m_vertices.resize(vertexCount);
    this->meshData->m_indices.resize(indexCount);

    // Calculate angle and step size
    float angleStep = pi2 / config.cone.segments;
    float angle = 0.0f;

    // Calculate top and bottom points
    glm::vec3 topPoint(0.0f, config.cone.height / 2.0f, 0.0f);
    glm::vec3 bottomPoint(0.0f, -config.cone.height / 2.0f, 0.0f);

    // Create top and bottom triangles
    this->meshData->m_vertices[0] = topPoint;
    this->meshData->m_vertices[vertexCount - 1] = bottomPoint;
    for (int i = 1; i <= config.cone.segments; i++) {
        // Calculate current angle
        angle = angleStep * i;

        // Calculate mPosition for current vertex on top and bottom circle
        glm::vec3 topVertex(config.cone.radius * glm::cos(angle), config.cone.height / 2.0f,
                            config.cone.radius * glm::sin(angle));
        glm::vec3 bottomVertex(config.cone.radius * glm::cos(angle), -config.cone.height / 2.0f,
                               config.cone.radius * glm::sin(angle));

        // Add m_vertices to m_vertices vector
        this->meshData->m_vertices[i] = topVertex;
        this->meshData->m_vertices[config.cone.segments + i] = bottomVertex;

        // Add this->meshData->m_indices for top and bottom triangles
        this->meshData->m_indices[(i - 1) * 3] = 0;
        this->meshData->m_indices[(i - 1) * 3 + 1] = i;
        this->meshData->m_indices[(i - 1) * 3 + 2] = i % config.cone.segments + 1;

        this->meshData->m_indices[(i + config.cone.segments - 1) * 3] = vertexCount - 1;
        this->meshData->m_indices[(i + config.cone.segments - 1) * 3 + 1] = config.cone.segments + i;
        this->meshData->m_indices[(i + config.cone.segments - 1) * 3 + 2] = config.cone.segments + i % config.cone.segments + 1;
    }

    // Set m_normals, m_tangents, and m_biTangents
//    calculateNormals();
//    calculateTangents();
}

void Geometry::buildTerrain(GeometryConfig config) {
    if (config.terrain.seed != 0) {
        srand(config.terrain.seed);
    }
    /// could take a seed in the config, grab a value from rand first to reseed the rand() function .. then set the seed
    /// when the function ends, reseed
    // Calculate the number of m_vertices and m_indices
    int numVertices = config.terrain.width * config.terrain.height;
    int numIndices = (config.terrain.width - 1) * (config.terrain.height - 1) * 6;

    // Resize the mPosition and index vectors
    this->meshData->m_vertices.resize(numVertices);
    this->meshData->m_indices.resize(numIndices);

    // Populate the mPosition vector with random config.terrain.heights
    for (int x = 0; x < config.terrain.width; ++x) {
        for (int z = 0; z < config.terrain.height; ++z) {
            int index = x + z * config.terrain.width;
            float y = config.terrain.minHeight + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX /
                                                                                                  (config.terrain.maxHeight -
                                                                                                   config.terrain.minHeight)));
            this->meshData->m_vertices[index] = glm::vec3(static_cast<float>(x) * config.terrain.cellSize, y,
                                          static_cast<float>(z) * config.terrain.cellSize);
        }
    }

    // Populate the index vector
    int index = 0;
    for (int x = 0; x < config.terrain.width - 1; ++x) {
        for (int z = 0; z < config.terrain.height - 1; ++z) {
            int a = x + z * config.terrain.width;
            int b = (x + 1) + z * config.terrain.width;
            int c = x + (z + 1) * config.terrain.width;
            int d = (x + 1) + (z + 1) * config.terrain.width;

            this->meshData->m_indices[index++] = a;
            this->meshData->m_indices[index++] = b;
            this->meshData->m_indices[index++] = c;
            this->meshData->m_indices[index++] = b;
            this->meshData->m_indices[index++] = d;
            this->meshData->m_indices[index++] = c;
        }
    }

    // reseed rand
    srand(time(nullptr));
}

