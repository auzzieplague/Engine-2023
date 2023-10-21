#include <Debug.h>
#include "AssetLoader.h"

std::string AssetLoader::assetsPath = "../assets";

std::string AssetLoader::loadShaderFile(std::string name) {
    std::string fullPath = assetsPath + "/shaders/agnostic/" + name;

    std::ifstream fileStream(fullPath);
    if (!fileStream.is_open()) {
        // Handle error, e.g., return an empty string or throw an exception
        Debug::show("yeah na, she cooked");
        return "";
    }

    std::stringstream shaderStream;
    shaderStream << fileStream.rdbuf();
    fileStream.close();

    return shaderStream.str();
}
