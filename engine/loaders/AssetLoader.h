#pragma once
#include <fstream>
#include <sstream>
#include <string>

class AssetLoader {
    // set asset directory
    // manage lookups
    // manage caching
    // responsible for passing the file contents back
    // initially were grabbing files from locations, but we will want to grab contents from indexed file paks.
public:

    static std::string assetsPath;
    static std::string loadShaderFile(std::string name); // shaderProgram will put contents into source


};

