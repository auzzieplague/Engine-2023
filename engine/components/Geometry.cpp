#pragma once

#include "Geometry.h"

void Geometry::buildQuad() {
    // Define the vertex positions
    std::vector<glm::vec3> vertices = {
            glm::vec3(-0.5f, 0.5f, 0.0f),
            glm::vec3(0.5f, 0.5f, 0.0f),
            glm::vec3(0.5f, -0.5f, 0.0f),
            glm::vec3(-0.5f, -0.5f, 0.0f)
    };

    // Define the indices of the two triangles that make m_up the quad
    std::vector<unsigned int> indices = {
            0, 1, 2,
            2, 3, 0
    };

    // Assign the vertex positions and indices to the mesh
    this->positions = vertices;
    this->indices = indices;
}

void Geometry::buildCube(GeometryConfig config) {
    config.box.sizeX=config.box.sizeY=config.box.sizeZ=config.cube.size;
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

    // Assign the vertex positions and indices to the mesh
    this->positions = vertices;
    this->indices = indices;
}

void Geometry::buildDome(GeometryConfig config) {
    positions.clear();
    indices.clear();

    // Generate the vertex positions
    for (unsigned int j = 0; j <= config.dome.segments; j++) {
        float y = cos(-pi / 2.0f + (float) j / (float) config.dome.segments * pi);
        float r = sin(-pi / 2.0f + (float) j / (float) config.dome.segments * pi) * config.dome.radius;

        for (unsigned int i = 0; i <= config.dome.segments; i++) {
            float x = cos((float) i / (float) config.dome.segments * 2.0f * pi) * r;
            float z = sin((float) i / (float) config.dome.segments * 2.0f * pi) * r;

            positions.emplace_back(x, y, z);
        }
    }

    // Generate the triangle indices
    for (unsigned int j = 0; j < config.dome.segments; j++) {
        for (unsigned int i = 0; i < config.dome.segments; i++) {
            unsigned int a = j * (config.dome.segments + 1) + i;
            unsigned int b = a + 1;
            unsigned int c = (j + 1) * (config.dome.segments + 1) + i;
            unsigned int d = c + 1;

            indices.push_back(a);
            indices.push_back(b);
            indices.push_back(d);

            indices.push_back(a);
            indices.push_back(d);
            indices.push_back(c);
        }
    }
}

void Geometry::buildSphere(GeometryConfig config)  {
    float const R = 1.0f / (float)(config.sphere.rings - 1);
    float const S = 1.0f / (float)(config.sphere.sectors - 1);
    float phi, theta;

    positions.clear();
    indices.clear();
    for(unsigned int r = 0; r < config.sphere.rings; ++r) {
        for(unsigned int s = 0; s < config.sphere.sectors; ++s) {
            phi =  pi * r * R;
            theta = 2.0f * pi * s * S;
            float x = sin(phi) * cos(theta);
            float y = cos(phi);
            float z = sin(phi) * sin(theta);
            positions.push_back(glm::vec3(x, y, z) * config.sphere.radius);
        }
    }

    for(unsigned int r = 0; r < config.sphere.rings - 1; ++r) {
        for(unsigned int s = 0; s < config.sphere.sectors - 1; ++s) {
            unsigned int idx = r * config.sphere.sectors + s;
            indices.push_back(idx);
            indices.push_back(idx + 1);
            indices.push_back((r + 1) * config.sphere.sectors + s + 1);
            indices.push_back((r + 1) * config.sphere.sectors + s + 1);
            indices.push_back((r + 1) * config.sphere.sectors + s);
            indices.push_back(idx);
        }
    }
}

void Geometry::buildCapsule(GeometryConfig config)
{
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
            positions.push_back(glm::vec3(x, y, z));
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
            positions.push_back(glm::vec3(x, y, z));
        }
    }

    // Create cylinder
    unsigned int topStart = 0;
    unsigned int bottomStart = positions.size() - (config.capsule.segments + 1);
    for (unsigned int j = 0; j < config.capsule.segments; j++) {
        unsigned int offset = j * (config.capsule.segments + 1);
        for (unsigned int i = 0; i < config.capsule.segments; i++) {
            indices.push_back(topStart + offset + i);
            indices.push_back(topStart + offset + i + 1);
            indices.push_back(bottomStart + offset + i);

            indices.push_back(bottomStart + offset + i);
            indices.push_back(topStart + offset + i + 1);
            indices.push_back(bottomStart + offset + i + 1);
        }
    }
}

/// torus has index glitch
void Geometry::buildTorus(GeometryConfig config) {
    positions.clear();
    indices.clear();

    float segmentAngle = pi2 / config.torus.segments;
    float sideAngle = pi2 / config.torus.sides;

    // Compute torus vertices
    for (int i = 0; i <= config.torus.segments; i++) {
        float phi = i * segmentAngle;
        glm::vec3 center(std::cos(phi), std::sin(phi), 0.0f);

        for (int j = 0; j <= config.torus.sides; j++) {
            float theta = j * sideAngle;
            glm::vec3 dir(std::cos(theta), std::sin(theta), 0.0f);
            glm::vec3 vertex = center * (config.torus.radius + config.torus.tubeRadius * std::cos(theta)) + dir * config.torus.tubeRadius * std::sin(theta);
            positions.push_back(vertex);
        }
    }

    // Compute torus indices
    for (int i = 0; i < config.torus.segments; i++) {
        int k1 = i * (config.torus.sides + 1);
        int k2 = k1 + config.torus.sides + 1;

        for (int j = 0; j < config.torus.sides; j++, k1++, k2++) {
            if (j == config.torus.sides - 1) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(i == config.torus.segments - 1 ? k2 - config.torus.sides - 1 : k1 - config.torus.sides - 1);

                indices.push_back(i == config.torus.segments - 1 ? k2 - config.torus.sides - 1 : k1 - config.torus.sides - 1);
                indices.push_back(k2);
                indices.push_back(i == config.torus.segments - 1 ? k1 : k2);
            }
            else {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);

                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
}

void Geometry::buildCone(GeometryConfig config) {

    // Calculate vertex and index counts
    int vertexCount = config.cone.segments * 2 + 2;
    int indexCount = config.cone.segments * 6;

    // Resize vectors to hold new data
    positions.resize(vertexCount);
    indices.resize(indexCount);

    // Calculate angle and step size
    float angleStep = pi2 / config.cone.segments;
    float angle = 0.0f;

    // Calculate top and bottom points
    glm::vec3 topPoint(0.0f, config.cone.height / 2.0f, 0.0f);
    glm::vec3 bottomPoint(0.0f, -config.cone.height / 2.0f, 0.0f);

    // Create top and bottom triangles
    positions[0] = topPoint;
    positions[vertexCount - 1] = bottomPoint;
    for (int i = 1; i <= config.cone.segments; i++)
    {
        // Calculate current angle
        angle = angleStep * i;

        // Calculate m_position for current vertex on top and bottom circle
        glm::vec3 topVertex(config.cone.radius * glm::cos(angle), config.cone.height / 2.0f, config.cone.radius * glm::sin(angle));
        glm::vec3 bottomVertex(config.cone.radius * glm::cos(angle), -config.cone.height / 2.0f, config.cone.radius * glm::sin(angle));

        // Add vertices to positions vector
        positions[i] = topVertex;
        positions[config.cone.segments + i] = bottomVertex;

        // Add indices for top and bottom triangles
        indices[(i - 1) * 3] = 0;
        indices[(i - 1) * 3 + 1] = i;
        indices[(i - 1) * 3 + 2] = i % config.cone.segments + 1;

        indices[(i + config.cone.segments - 1) * 3] = vertexCount - 1;
        indices[(i + config.cone.segments - 1) * 3 + 1] = config.cone.segments + i;
        indices[(i + config.cone.segments - 1) * 3 + 2] = config.cone.segments + i % config.cone.segments + 1;
    }

    // Set normals, tangents, and bitangents
//    calculateNormals();
//    calculateTangents();
}

void Geometry::buildTerrain(GeometryConfig config) {
    if (config.terrain.seed != 0) {
        srand(config.terrain.seed);
    }
    /// could take a seed in the config, grab a value from rand first to reseed the rand() function .. then set the seed
    /// when the function ends, reseed
    // Calculate the number of vertices and indices
    int numVertices = config.terrain.width * config.terrain.height;
    int numIndices = (config.terrain.width - 1) * (config.terrain.height - 1) * 6;

    // Resize the m_position and index vectors
    positions.resize(numVertices);
    indices.resize(numIndices);

    // Populate the m_position vector with random config.terrain.heights
    for (int x = 0; x < config.terrain.width; ++x) {
        for (int z = 0; z < config.terrain.height; ++z) {
            int index = x + z * config.terrain.width;
            float y = config.terrain.minHeight + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (config.terrain.maxHeight - config.terrain.minHeight)));
            positions[index] = glm::vec3(static_cast<float>(x) * config.terrain.cellSize, y, static_cast<float>(z) * config.terrain.cellSize);
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

            indices[index++] = a;
            indices[index++] = b;
            indices[index++] = c;
            indices[index++] = b;
            indices[index++] = d;
            indices[index++] = c;
        }
    }

    // reseed rand
    srand(time(nullptr));
}

