#pragma once

#include "../../core/Base.h"
#include "stb_image.h"
#include "components/meshes/Mesh.h"

/**
* the function of this class is to load, cache, package (compress, decompress) assets
* this layer of abstraction should allow dev to use dev folders while prod can use packaged assets
 * we will reference assets by category and name or reverse lookup by ID`
*/

class AssetManager {
    //todo shader
private:
    static std::map<std::string, std::string> category_path;
public:
    static std::string getPath(const std::string& category);

    static std::string getRelativePath(std::string category, std::string assetName);

    static std::string stringFromFile(std::string &path);

    // loads or retrieves from cache - the specified height map
    static HeightMap getHeightMap ( const std::string &name, float scale = 1, float minHeight = 0, float maxHeight = 1);

    static Mesh *getMeshFromHeightMap(const std::string &filePath, float heightScale, float uvScale, bool flipTriangles = true);
};


