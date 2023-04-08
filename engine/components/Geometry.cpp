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

    // Define the indices of the two triangles that make up the quad
    std::vector<unsigned int> indices = {
            0, 1, 2,
            2, 3, 0
    };

    // Assign the vertex positions and indices to the mesh
    this->positions = vertices;
    this->indices = indices;
}

void Geometry::buildCube() {
    std::vector<glm::vec3> vertices = {
            // Front face
            glm::vec3(-0.5f, -0.5f, 0.5f),
            glm::vec3(0.5f, -0.5f, 0.5f),
            glm::vec3(0.5f, 0.5f, 0.5f),
            glm::vec3(-0.5f, 0.5f, 0.5f),
            // Back face
            glm::vec3(0.5f, -0.5f, -0.5f),
            glm::vec3(-0.5f, -0.5f, -0.5f),
            glm::vec3(-0.5f, 0.5f, -0.5f),
            glm::vec3(0.5f, 0.5f, -0.5f),
            // Top face
            glm::vec3(-0.5f, 0.5f, 0.5f),
            glm::vec3(0.5f, 0.5f, 0.5f),
            glm::vec3(0.5f, 0.5f, -0.5f),
            glm::vec3(-0.5f, 0.5f, -0.5f),
            // Bottom face
            glm::vec3(-0.5f, -0.5f, -0.5f),
            glm::vec3(0.5f, -0.5f, -0.5f),
            glm::vec3(0.5f, -0.5f, 0.5f),
            glm::vec3(-0.5f, -0.5f, 0.5f),
            // Right face
            glm::vec3(0.5f, -0.5f, 0.5f),
            glm::vec3(0.5f, -0.5f, -0.5f),
            glm::vec3(0.5f, 0.5f, -0.5f),
            glm::vec3(0.5f, 0.5f, 0.5f),
            // Left face
            glm::vec3(-0.5f, -0.5f, -0.5f),
            glm::vec3(-0.5f, -0.5f, 0.5f),
            glm::vec3(-0.5f, 0.5f, 0.5f),
            glm::vec3(-0.5f, 0.5f, -0.5f),
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

void Geometry::buildDome(float radius, unsigned int segments) {
    positions.clear();
    indices.clear();

    // Generate the vertex positions
    for (unsigned int j = 0; j <= segments; j++) {
        float y = cos(-pi / 2.0f + (float) j / (float) segments * pi);
        float r = sin(-pi / 2.0f + (float) j / (float) segments * pi) * radius;

        for (unsigned int i = 0; i <= segments; i++) {
            float x = cos((float) i / (float) segments * 2.0f * pi) * r;
            float z = sin((float) i / (float) segments * 2.0f * pi) * r;

            positions.emplace_back(x, y, z);
        }
    }

    // Generate the triangle indices
    for (unsigned int j = 0; j < segments; j++) {
        for (unsigned int i = 0; i < segments; i++) {
            unsigned int a = j * (segments + 1) + i;
            unsigned int b = a + 1;
            unsigned int c = (j + 1) * (segments + 1) + i;
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

void Geometry::buildSphere(float radius, unsigned int rings, unsigned int sectors)  {
    float const R = 1.0f / (float)(rings - 1);
    float const S = 1.0f / (float)(sectors - 1);
    float phi, theta;

    positions.clear();
    indices.clear();
    for(unsigned int r = 0; r < rings; ++r) {
        for(unsigned int s = 0; s < sectors; ++s) {
            phi =  pi * r * R;
            theta = 2.0f * pi * s * S;
            float x = sin(phi) * cos(theta);
            float y = cos(phi);
            float z = sin(phi) * sin(theta);
            positions.push_back(glm::vec3(x, y, z) * radius);
        }
    }

    for(unsigned int r = 0; r < rings - 1; ++r) {
        for(unsigned int s = 0; s < sectors - 1; ++s) {
            unsigned int idx = r * sectors + s;
            indices.push_back(idx);
            indices.push_back(idx + 1);
            indices.push_back((r + 1) * sectors + s + 1);
            indices.push_back((r + 1) * sectors + s + 1);
            indices.push_back((r + 1) * sectors + s);
            indices.push_back(idx);
        }
    }
}

void Geometry::buildCapsule(float radius, float halfLength, unsigned int segments)
{
    float segmentAngle = pi2 / segments;

    // Create top hemisphere
    for (unsigned int j = 0; j <= segments / 4; j++) {
        float inclination = segmentAngle * j;
        float z = radius * cos(inclination) + halfLength - radius;
        float xy = radius * sin(inclination);
        for (unsigned int i = 0; i <= segments; i++) {
            float azimuth = segmentAngle * i;
            float x = xy * cos(azimuth);
            float y = xy * sin(azimuth);
            positions.push_back(glm::vec3(x, y, z));
        }
    }

    // Create bottom hemisphere
    for (unsigned int j = 3 * segments / 4; j <= segments; j++) {
        float inclination = segmentAngle * j;
        float z = radius * cos(inclination) - halfLength + radius;
        float xy = radius * sin(inclination);
        for (unsigned int i = 0; i <= segments; i++) {
            float azimuth = segmentAngle * i;
            float x = xy * cos(azimuth);
            float y = xy * sin(azimuth);
            positions.push_back(glm::vec3(x, y, z));
        }
    }

    // Create cylinder
    unsigned int topStart = 0;
    unsigned int bottomStart = positions.size() - (segments + 1);
    for (unsigned int j = 0; j < segments; j++) {
        unsigned int offset = j * (segments + 1);
        for (unsigned int i = 0; i < segments; i++) {
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
void Geometry::buildTorus(float radius, float tubeRadius, int segments, int sides) {
    positions.clear();
    indices.clear();

    float segmentAngle = pi2 / segments;
    float sideAngle = pi2 / sides;

    // Compute torus vertices
    for (int i = 0; i <= segments; i++) {
        float phi = i * segmentAngle;
        glm::vec3 center(std::cos(phi), std::sin(phi), 0.0f);

        for (int j = 0; j <= sides; j++) {
            float theta = j * sideAngle;
            glm::vec3 dir(std::cos(theta), std::sin(theta), 0.0f);
            glm::vec3 vertex = center * (radius + tubeRadius * std::cos(theta)) + dir * tubeRadius * std::sin(theta);
            positions.push_back(vertex);
        }
    }

    // Compute torus indices
    for (int i = 0; i < segments; i++) {
        int k1 = i * (sides + 1);
        int k2 = k1 + sides + 1;

        for (int j = 0; j < sides; j++, k1++, k2++) {
            if (j == sides - 1) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(i == segments - 1 ? k2 - sides - 1 : k1 - sides - 1);

                indices.push_back(i == segments - 1 ? k2 - sides - 1 : k1 - sides - 1);
                indices.push_back(k2);
                indices.push_back(i == segments - 1 ? k1 : k2);
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

void Geometry::buildCone(float radius, float height, int segments) {

    // Calculate vertex and index counts
    int vertexCount = segments * 2 + 2;
    int indexCount = segments * 6;

    // Resize vectors to hold new data
    positions.resize(vertexCount);
    indices.resize(indexCount);

    // Calculate angle and step size
    float angleStep = pi2 / segments;
    float angle = 0.0f;

    // Calculate top and bottom points
    glm::vec3 topPoint(0.0f, height / 2.0f, 0.0f);
    glm::vec3 bottomPoint(0.0f, -height / 2.0f, 0.0f);

    // Create top and bottom triangles
    positions[0] = topPoint;
    positions[vertexCount - 1] = bottomPoint;
    for (int i = 1; i <= segments; i++)
    {
        // Calculate current angle
        angle = angleStep * i;

        // Calculate position for current vertex on top and bottom circle
        glm::vec3 topVertex(radius * glm::cos(angle), height / 2.0f, radius * glm::sin(angle));
        glm::vec3 bottomVertex(radius * glm::cos(angle), -height / 2.0f, radius * glm::sin(angle));

        // Add vertices to positions vector
        positions[i] = topVertex;
        positions[segments + i] = bottomVertex;

        // Add indices for top and bottom triangles
        indices[(i - 1) * 3] = 0;
        indices[(i - 1) * 3 + 1] = i;
        indices[(i - 1) * 3 + 2] = i % segments + 1;

        indices[(i + segments - 1) * 3] = vertexCount - 1;
        indices[(i + segments - 1) * 3 + 1] = segments + i;
        indices[(i + segments - 1) * 3 + 2] = segments + i % segments + 1;
    }

    // Set normals, tangents, and bitangents
//    calculateNormals();
//    calculateTangents();
}

void Geometry::buildTerrain(int width, int height, float minHeight, float maxHeight, float cellSize) {
    // Calculate the number of vertices and indices
    int numVertices = width * height;
    int numIndices = (width - 1) * (height - 1) * 6;

    // Resize the position and index vectors
    positions.resize(numVertices);
    indices.resize(numIndices);

    // Populate the position vector with random heights
    for (int x = 0; x < width; ++x) {
        for (int z = 0; z < height; ++z) {
            int index = x + z * width;
            float y = minHeight + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxHeight - minHeight)));
            positions[index] = glm::vec3(static_cast<float>(x) * cellSize, y, static_cast<float>(z) * cellSize);
        }
    }

    // Populate the index vector
    int index = 0;
    for (int x = 0; x < width - 1; ++x) {
        for (int z = 0; z < height - 1; ++z) {
            int a = x + z * width;
            int b = (x + 1) + z * width;
            int c = x + (z + 1) * width;
            int d = (x + 1) + (z + 1) * width;

            indices[index++] = a;
            indices[index++] = b;
            indices[index++] = c;
            indices[index++] = b;
            indices[index++] = d;
            indices[index++] = c;
        }
    }
}