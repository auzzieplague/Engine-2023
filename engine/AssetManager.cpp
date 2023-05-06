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
        const std::string &name, float scale , float minHeight, float maxHeight) {

    /// note: no need to cache a height map, it likely won't be used more than once in the same scene

    auto filename = getRelativePath("heightmaps",  name + ".png");
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

    int size = width*height;
    // Allocate memory for height map data
    heightMap.vertexHeights.resize(size);
    heightMap.uvCoordinates.resize(size);
    heightMap.normalVectors.resize(size);
    heightMap.colorData.resize(size);

    int i=0;
    for (int y = 0; y < height; y++) {
//        heightMap.vertexHeights[y].resize(width);
//        heightMap.uvCoordinates[y].resize(width);
//        heightMap.normalVectors[y].resize(width);
//        heightMap.colorData[y].resize(width);
        for (int x = 0; x < width; x++) {
            // Calculate height value from image data
            float heightValue =
                    minHeight + (maxHeight - minHeight) * imageData[(y * width + x) * numComponents] / 255.0f;
            heightMap.vertexHeights[i] = heightValue;

            // Set UV coordinates to match vertex position
//            heightMap.uvCoordinates[y][x] = glm::vec2(x * 1.0f / (width - 1), y * 1.0f / (height - 1));
//            heightMap.uvCoordinates[y][x] = {x * 1.0f / (width - 1), y * 1.0f / (height - 1)};
        i++;
        }
    }

//     Free image data
    stbi_image_free(imageData);

    return heightMap;
}
