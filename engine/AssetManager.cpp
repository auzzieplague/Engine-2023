#pragma once
#define STB_IMAGE_IMPLEMENTATION

#include "AssetManager.h"
#include "components/meshes/Mesh.h"

#define DEV_MODE

#ifdef DEV_MODE
std::map<std::string, std::string> AssetManager::category_path = {
        {"shaders_opengl", "shaders/glsl"},
        {"heightmap",      "heightmaps"},
        {"defaults",       "materials/defaults"},
        {"material",       "materials"},
        {"mats_ground",    "materials/ground"},
        {"icons",    "icons"},
};
#else
/// should be pulling from packages in live mode anyway
std::map<std::string, std::string> AssetManager::category_path = {
        {"shaders_opengl", "shaders/glsl"},
        {"trees",          "models/landscape/foliage"},
        {"rocks",          "models/landscape/rocks"},
};
#endif

std::string AssetManager::getPath(const std::string &category) {
    auto assetPathPrefix = "../assets/";
    auto it = category_path.find(category);
    // if there's no match for category then reference in code is an error
    assert(it != category_path.end() && "Asset category was not found");
    return assetPathPrefix + it->second;
}

std::string AssetManager::getRelativePath(std::string category, std::string assetName) {

//    std::string filename = getPath(category) + "/" + assetName;
    return getPath(category) + "/" + assetName;
}

std::string AssetManager::stringFromFile(std::string &path) {
    std::ifstream file(path);
    if (file.fail()) {
        std::cout << "unable to open file " << path << std::endl;
    }

    std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return str;
}

HeightMap AssetManager::getHeightMap(
        const std::string &name,
        float scale, float minHeight,
        float maxHeight) {

    auto filename = getRelativePath("heightmap", name + ".png");
    HeightMap heightMap;
    int width, height, numComponents;
    unsigned char *imageData = stbi_load(filename.c_str(), &width, &height, &numComponents, 0);
    if (!imageData) {
        throw std::runtime_error("Failed to load image");
    }

    // Set height map properties
    heightMap.width = width;
    heightMap.height = height;
    heightMap.scale = scale;
    heightMap.minHeight = minHeight;
    heightMap.maxHeight = maxHeight;

    int size = width * height;
    // Allocate memory for height map data
    heightMap.vertexHeights.resize(size);
    heightMap.indices.resize(6 * (width - 1) * (height - 1));
    heightMap.uvCoordinates.resize(2 * size);
    heightMap.vertices.resize(3 * size);

    int i = 0, index = 0;
    for (int y = 0; y < height - 1; y++) {
        for (int x = 0; x < width - 1; x++) {
            // Calculate height value from image data

            float heightValue =
                    minHeight + (maxHeight - minHeight) * imageData[(y * width + x) * numComponents] / 255.0f;

            heightMap.vertexHeights[i] = heightValue * scale;

            // Calculate vertex position based on (x,y,height) coordinates
            float xPos = (float) x / (width - 1);
            float yPos = heightValue;
            float zPos = (float) y / (height - 1);

            heightMap.vertices[i * 3] = xPos;
            heightMap.vertices[i * 3 + 1] = yPos;
            heightMap.vertices[i * 3 + 2] = zPos;

            float u = (float) x / (float) (width - 1);
            float v = (float) y / (float) (height - 1);
            heightMap.uvCoordinates[2 * (y * width + x) + 0] = u;
            heightMap.uvCoordinates[2 * (y * width + x) + 1] = v;

            if (x < width - 3 && y < height - 2) {
                // Add indices for two triangles of the quad
                heightMap.indices[index++] = i;
                heightMap.indices[index++] = i + 1;
                heightMap.indices[index++] = i + width;

                heightMap.indices[index++] = i + 1;
                heightMap.indices[index++] = i + width + 1;
                heightMap.indices[index++] = i + width;
            }

            i++;
        }
    }

//     Free image data
    stbi_image_free(imageData);

    return heightMap;
}

Mesh *
AssetManager::getMeshFromHeightMap(const std::string &fileName, float heightScale, float uvScale, bool flipTriangles) {

    auto filename = getRelativePath("heightmap", fileName + ".png");
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
    Mesh *mesh = new Mesh();
    mesh->setVertices(vertices);
    mesh->setIndices(indices);
    mesh->setUVs(uv);
    mesh->setNormals(normals);
//    mesh->setTangents(m_tangents);
//    mesh->setBiTangents(m_biTangents);
    return mesh;
}