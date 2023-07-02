#pragma once

#include "../../core/Base.h"
#include "stb_image.h"
#include "components/meshes/Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <filesystem>


namespace fs = std::filesystem;

/**
* the function of this class is to load, cache, package (compress, decompress) assets
* this layer of abstraction should allow dev to use dev folders while prod can use packaged assets
 * we will reference assets by category and name or reverse lookup by ID`
*/

class AssetManager {
    //todo shader
private:
    static std::map<std::string, std::string> category_path;
    static std::vector<std::string> fileList;
public:
    static const std::vector<std::string> &getFileList();

public:

    static std::string getPath(const std::string &category);

    static std::string getRelativePath(std::string category, std::string assetName);

    static std::string stringFromFile(std::string &path);

    // loads or retrieves from cache - the specified height map
    static HeightMap getHeightMap(const std::string &name, float scale = 1, float minHeight = 0, float maxHeight = 1);

    static Mesh *
    getMeshFromHeightMap(const std::string &filePath, float heightScale, float uvScale, bool flipTriangles = true);

    static void testASSIMP();

    static void initialise() {
        refreshAssets();
    }

    static void refreshAssets() {
        fileList = buildDirectoryStructure("..\\assets");
    }

    static std::vector<std::string> buildDirectoryStructure(const std::string &directoryPath) {
        std::vector<std::string> structure;
        readDirectory(directoryPath, structure);
        // Print the fileList
        for (const auto &file: structure) {
            std::cout << file << std::endl;
        }
        return structure;
    }

    static void readDirectory(const std::string &directoryPath, std::vector<std::string> &fileList) {
        // Iterate over the directory
        for (const auto &entry: fs::directory_iterator(directoryPath)) {
            if (fs::is_directory(entry)) {
                // If the entry is a directory, recursively read its contents
                std::vector<std::string> subFileList;
                readDirectory(entry.path().string(), subFileList);

                // Add the subFileList as a single entry in the fileList vector
                fileList.push_back(entry.path().string() + " (Directory)");
                fileList.insert(fileList.end(), subFileList.begin(), subFileList.end());
            } else if (fs::is_regular_file(entry)) {
                // If the entry is a regular file, add its path to the fileList vector
                fileList.push_back(entry.path().string());
            }
        }
    }
};


