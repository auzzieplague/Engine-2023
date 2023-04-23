#pragma once

#include "AssetManager.h"

#define DEVMODE

#ifdef DEVMODE
std::map<std::string, std::string> AssetManager::category_path = {
        {"shaders_opengl", "../assets/shaders/glsl"},
        {"trees",          "../../assets/models/landscape/foliage"},
        {"rocks",          "../../assets/models/landscape/rocks"},
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
    auto it = category_path.find(category);
    // if there's no match for category then reference in code is an error
    assert(it != category_path.end());
    return it->second;
}

std::string AssetManager::getRelativePath(std::string category, std::string assetName) {

    std::string filename = getPath(category) + "/" + assetName;
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
