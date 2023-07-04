#pragma once

#include "../../core/Base.h"
#include "stb_image.h"
#include "components/meshes/Mesh.h"
#include "components/Model.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <filesystem>
#include <imgui.h>

namespace fs = std::filesystem;

class FileStructure {
public:
    explicit FileStructure(const std::string &name, bool isDirectory = false)
            : mPath(name), mIsDirectory(isDirectory) {
        mName = ExtractFilename(name);
        //get file extension and set isLoadable

        auto extension = getFileExtension(mName);
        if (extension == "obj") {
            isLoadable = true;
        }
    }

    FileStructure() = default;

    void AddChild(const FileStructure &child) {
        mChildren.push_back(child);
    }

    void RenderImGuiTree() const {
        RenderImGuiTreeRecursive(*this);
    }

    std::string getFileExtension(const std::string& fileName) {
        size_t dotIndex = fileName.find_last_of('.');
        if (dotIndex != std::string::npos && dotIndex < fileName.length() - 1) {
            return fileName.substr(dotIndex + 1);
        }
        return "";  // No file extension found
    }

protected:
    friend class AssetManager;

    std::string mPath;
    std::string mName;
    bool isLoadable = false;
    bool mIsDirectory = false;
    std::vector<FileStructure> mChildren;

    static FileStructure buildFileStructure(const std::string &path) {
        FileStructure root(path, true);

        for (const auto &entry: std::filesystem::directory_iterator(path)) {
            std::string name = entry.path().filename().string();
            bool isDirectory = std::filesystem::is_directory(entry.path());

            if (isDirectory) {
                FileStructure subdirectory = buildFileStructure(entry.path().string());
                root.AddChild(subdirectory);
            } else {
                root.AddChild(FileStructure(name));
            }
        }

        return root;
    }

    void RenderImGuiTreeRecursive(const FileStructure &item) const {
        if (item.mIsDirectory) {

            bool open = ImGui::TreeNodeEx(item.mName.c_str(), ImGuiTreeNodeFlags_OpenOnArrow);
            if (open) {
                for (const auto &child: item.mChildren) {
                    RenderImGuiTreeRecursive(child);
                }
                ImGui::TreePop();
            }
            return;
        }

        ImGui::TreeNodeEx(item.mName.c_str(), ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen);
        ImGui::SameLine();
        ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.5f, 0.5f));
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4.0f, 2.0f));
        if (item.isLoadable && ImGui::Button("Load")) {
            Debug::show("load model");
        }
        ImGui::PopStyleVar(2);
    }


    std::string ExtractFilename(const std::string &path) {
        size_t lastSlashIndex = path.find_last_of("/\\");
        if (lastSlashIndex != std::string::npos) {
            return path.substr(lastSlashIndex + 1);
        }
        return path;
    }
};

/**
* the function of this class is to load, cache, package (compress, decompress) assets
* this layer of abstraction should allow dev to use dev folders while prod can use packaged assets
 * we will reference assets by category and name or reverse lookup by ID`
*/
class AssetManager {
    //todo shader
private:
    static std::map<std::string, std::string> category_path;
//    static std::vector<std::string> fileList;
    static FileStructure assetStructure;
public:
    static const FileStructure &getAssetStructure();

public:

public:

    static std::string getPath(const std::string &category);

    static std::string getRelativePath(std::string category, std::string assetName);

    static std::string stringFromFile(std::string &path);

    // loads or retrieves from cache - the specified height map
    static HeightMap getHeightMap(const std::string &name, float scale = 1, float minHeight = 0, float maxHeight = 1);

    static Mesh *
    getMeshFromHeightMap(const std::string &filePath, float heightScale, float uvScale, bool flipTriangles = true);

    static void testASSIMP();

    static Model *loadModelFromFile (const std::string& filePath);

    static void initialise() {
        refreshAssets();
    }

    static void refreshAssets() {
        // manually add assets level
        // then add multiple children for models, materials etc.
        assetStructure = FileStructure::buildFileStructure("..\\assets");
    }
};


