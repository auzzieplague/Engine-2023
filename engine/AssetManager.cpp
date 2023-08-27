#pragma once
#define STB_IMAGE_IMPLEMENTATION

#include "AssetManager.h"
#include "components/meshes/Mesh.h"
#include "components/meshes/MeshData.h"

#define DEV_MODE

#ifdef DEV_MODE
std::string AssetManager::assetPathPrefix = "../assets/";
std::map<std::string, std::string> AssetManager::category_path = {
        {"model",          "models"},
        {"shaders_opengl", "shaders/glsl"},
        {"heightmap",      "heightmaps"},
        {"default",        "materials/default"},
        {"material",       "materials"},
        {"mats_ground",    "materials/ground"},
        {"icons",          "icons"},
};
#else
/// should be pulling from packages in live mode anyway
std::map<std::string, std::string> AssetManager::category_path = {
        {"shaders_opengl", "shaders/glsl"},
        {"trees",          "models/landscape/foliage"},
        {"rocks",          "models/landscape/rocks"},
};
#endif

FileStructure AssetManager::assetStructure;
std::map<std::string,MeshData *>AssetManager::meshPool;

std::string AssetManager::getPath(const std::string &category) {
//    auto assetPathPrefix = "../assets/";
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

void AssetManager::testASSIMP() {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(getRelativePath("model", "testModel.obj"), aiProcess_Triangulate);
    if (scene != nullptr && scene->HasMeshes()) {
        Debug::show("[->] assimp load test passed");
    } else {
        Debug::show("[->] assimp failed to load testModel.obj");
    }
}

const FileStructure &AssetManager::getAssetStructure() {
    return assetStructure;
}

Mesh *AssetManager::populateMeshFromAiMesh(aiMesh *mesh) {
    auto *ourMesh = new Mesh();
    auto *ourMeshData = new MeshData();

    // Populate the vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        aiVector3D vertex = mesh->mVertices[i];
        glm::vec3 glmVertex(vertex.x, vertex.y, vertex.z);
        ourMeshData->addVertex(glmVertex);
    }

    // Populate the UVs (Texture Coordinates)
    if (mesh->HasTextureCoords(0)) {
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            aiVector3D uv = mesh->mTextureCoords[0][i];
            glm::vec2 glmUV(uv.x, uv.y);
            ourMeshData->addUV(glmUV);
        }
    }

    // Populate the normals
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        aiVector3D normal = mesh->mNormals[i];
        glm::vec3 glmNormal(normal.x, normal.y, normal.z);
        ourMeshData->addNormal(glmNormal);
    }

    // Populate the indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            unsigned int index = face.mIndices[j];
            ourMeshData->addIndex(index);
        }
    }

    ourMesh->meshData = ourMeshData;
    return ourMesh;
}

bool AssetManager::jsonContains(const nlohmann::json &jsonObject, const std::vector<std::string> &keys) {
    for (const std::string &key: keys) {
        if (!jsonObject.contains(key)) {
            return false;
        }
    }
    return true;
}

Model *AssetManager::loadModel(const std::string &modelName) {
    // get path to models
    auto filePath = "..\\assets\\models\\store\\" + modelName + ".json";
    auto jsonData = jsonFileToArray(filePath);
    auto model = new Model();
    model->setName(jsonData["name"]);

    if (jsonData.contains("position")) {
        model->setPosition(getVectorFromJson(jsonData, "position"));
    }

    if (jsonData.contains("meshes") && jsonData["meshes"].is_array()) {
        for (auto mesh: jsonData["meshes"]) {
            Mesh *newMesh = getMeshFromJson(mesh);
            model->addChild(newMesh); // add functionality to automatically add root when empty
        }
    }

    model->setSelectable();

    return model;
}

Mesh *AssetManager::getExistingMeshDataForPath(const std::string &filePath) {
//    return nullptr;
    if ( !AssetManager::meshPool[filePath]) {
        return nullptr;
    }
    auto mesh = new Mesh();
    mesh->meshData = AssetManager::meshPool[filePath];
//    Debug::show("using existing " + mesh->meshData->getIdentifier());
    return mesh;
}

Mesh *AssetManager::loadMeshFromFile(const std::string &filePath) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(assetPathPrefix+filePath,
                                             aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "Error loading model file: " << importer.GetErrorString() << std::endl;
        return nullptr;
    }

    aiMesh *mesh = scene->mMeshes[0];

    // todo mark as instanced, add to lookup table
    Mesh* ourMesh = getExistingMeshDataForPath(filePath);
    if (!ourMesh){
        ourMesh = populateMeshFromAiMesh(mesh);
        AssetManager::meshPool[filePath] = ourMesh->meshData;
    }
    return ourMesh;
}

Model *AssetManager::loadModelFromFile(const std::string &filePath) {
    auto *ourModel = new Model();
    ourModel->setFilePath(filePath);
    auto ourMesh = loadMeshFromFile(filePath);

    ourMesh->setSelectable();
    ourModel->addChild(ourMesh);
    ourModel->mRootMesh = ourMesh;
    ourModel->mRootMesh->parentComponent = ourModel;
    ourModel->mRootMesh->rootComponent = ourModel;
    ourMesh->setMaterial(*Material::defaultMaterial);
    ourModel->setLocalRotation({0, 0, 0});

    return ourModel;
}

void AssetManager::initialise() {
    refreshAssets();
}

void AssetManager::refreshAssets() {
    // manually add assets level
    // then add multiple children for models, materials etc.
    assetStructure = FileStructure::buildFileStructure("..\\assets\\models");
}

void AssetManager::checkFileExists(const std::string &filePath) {
    if (!std::filesystem::exists(filePath)) {
        Debug::throwFileNotFound(filePath);
    }
}

std::string AssetManager::removeComments(std::string &stringWithComments) {
    std::string result;
    size_t pos = 0;
    size_t length = stringWithComments.length();
    bool inMultiLineComment = false;

    while (pos < length) {
        // Find the beginning of a comment block (/*) or a single-line comment (//)
        size_t multiLineCommentStart = stringWithComments.find("/*", pos);
        size_t singleLineCommentStart = stringWithComments.find("//",
                                                                pos);// Check which comment type comes first in the input
        if (multiLineCommentStart == std::string::npos && singleLineCommentStart == std::string::npos) {
            // No comments found, add the remaining part of the input to the result
            result += stringWithComments.substr(pos);
            break;
        }
        if (singleLineCommentStart == std::string::npos ||
            (multiLineCommentStart != std::string::npos && multiLineCommentStart < singleLineCommentStart)) {
            // Add the content before the multi-line comment to the result
            result += stringWithComments.substr(pos, multiLineCommentStart - pos);
            // Find the end of the multi-line comment (*/)
            size_t commentEnd = stringWithComments.find("*/", multiLineCommentStart + 2);
            if (commentEnd == std::string::npos) {
                // If no end of multi-line comment found, exit the loop
                break;
            }
            // Move the position past the multi-line comment
            pos = commentEnd + 2;
        } else {
            // Add the content before the single-line comment to the result
            result += stringWithComments.substr(pos, singleLineCommentStart - pos);
            // Find the end of the single-line comment (newline character)
            size_t commentEnd = stringWithComments.find('\n', singleLineCommentStart + 2);
            if (commentEnd == std::string::npos) {
                // If no end of single-line comment found, exit the loop
                break;
            }
            // Move the position past the single-line comment
            pos = commentEnd + 1;
        }
    }

    stringWithComments = result;
    return result;
}

nlohmann::json AssetManager::jsonFileToArray(const std::string &filePath) {
    checkFileExists(filePath);

    using json = nlohmann::json;
    std::ifstream t(filePath);

    std::string jsonString((std::istreambuf_iterator<char>(t)),
                           std::istreambuf_iterator<char>());

    removeComments(jsonString);

    json structure;
    try {
        structure = json::parse(jsonString);
        return structure;
    } catch (...) {
        return structure;
    }
}

glm::vec3 AssetManager::getVectorFromJson(nlohmann::json json, std::string key) {
    glm::vec3 vector;
    if (json.contains(key)) {
        if (jsonContains(json[key], {"x", "y", "z"})) {
            vector.x = json[key]["x"].get<std::float_t>();
            vector.y = json[key]["y"].get<std::float_t>();
            vector.z = json[key]["z"].get<std::float_t>();
        }
    }
    return vector;
}

Mesh *AssetManager::getMeshFromJson(nlohmann::json jsonMesh) {
    if (!jsonContains(jsonMesh, {"name", "path"})) {
        Debug::throwMissingItem("required keys", "json mesh construction");
    };

    std::string path = assetPathPrefix + jsonMesh["path"].get<std::string>();
    Mesh *mesh = loadMeshFromFile(path);

    if (!mesh) {
        Debug::throwFileNotFound(jsonMesh["path"]);
    };

    mesh->setName(jsonMesh["name"].get<std::string>());

    if (jsonMesh.contains("position")) {
        mesh->setPosition(getVectorFromJson(jsonMesh, "position"));
    }

    if (jsonMesh.contains("scale")) {
        mesh->setLocalScale(getVectorFromJson(jsonMesh, "scale"));
    }

    if (jsonMesh.contains("rotation")) {
        mesh->setLocalRotation(getVectorFromJson(jsonMesh, "rotation"));
    }

    if (jsonMesh.contains("material")) {
        // add materials - if no materials then add default material
        // will need to upgrade materials system

    } else {
        mesh->setMaterial(*Material::defaultMaterial);
    }


    return mesh;
}
