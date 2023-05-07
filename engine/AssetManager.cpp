#pragma once
#define STB_IMAGE_IMPLEMENTATION

#include "AssetManager.h"

#define DEVMODE

#ifdef DEVMODE
std::map<std::string, std::string> AssetManager::category_path = {
        {"shaders_opengl", "shaders/glsl"},
        {"heightmaps",     "heightmaps"},
        {"trees",          "models/landscape/foliage"},
        {"rocks",          "models/landscape/rocks"},
};
#else
/// should be pulling from packages in live mode anyway
std::map<std::string, std::string> AssetManager::category_path = {
        {"shaders_opengl", "shaders/glsl"},
        {"trees",          "models/landscape/foliage"},
        {"rocks",          "models/landscape/rocks"},
};
#endif

std::string AssetManager::getPath(std::string category) {
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

    auto filename = getRelativePath("heightmaps", name + ".png");
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

    int i = 0,index = 0;
    for (int y = 0; y < height-1; y++) {
        for (int x = 0; x < width-1; x++) {
            // Calculate height value from image data

            float heightValue =
                    minHeight + (maxHeight - minHeight) * imageData[(y * width + x) * numComponents] / 255.0f;

            heightMap.vertexHeights[i] = heightValue*scale;

            // Calculate vertex position based on (x,y,height) coordinates
            float xPos = (float)x / (width - 1) ;
            float yPos = heightValue ;
            float zPos = (float)y / (height - 1) ;

            heightMap.vertices[i * 3] = xPos ;
            heightMap.vertices[i * 3 + 1] = yPos;
            heightMap.vertices[i * 3 + 2] = zPos ;

            float u = (float)x / (float)(width - 1);
            float v = (float)y / (float)(height - 1);
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
