#pragma once

#include "../../core/Base.h"
#include "stb_image.h"
#include "components/meshes/Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <filesystem>
#include <imgui.h>

namespace fs = std::filesystem;

class FileSystemItem {
public:
    explicit FileSystemItem(const std::string& name, bool isDirectory = false)
            : mName(name), mIsDirectory(isDirectory) {}

    FileSystemItem()= default;
    void AddChild(const FileSystemItem& child) {
        mChildren.push_back(child);
    }

    void RenderImGuiTree() const {
        RenderImGuiTreeRecursive(*this);
    }

protected:
    friend class AssetManager;
    std::string mName;
    bool mIsDirectory = false;
    std::vector<FileSystemItem> mChildren;

    static FileSystemItem buildFileStructure(const std::string& path) {
        FileSystemItem root(path, true);

        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            std::string name = entry.path().filename().string();
            bool isDirectory = std::filesystem::is_directory(entry.path());

            if (isDirectory) {
                FileSystemItem subdirectory = buildFileStructure(entry.path().string());
                root.AddChild(subdirectory);
            } else {
                root.AddChild(FileSystemItem(name));
            }
        }

        return root;
    }

    void RenderImGuiTreeRecursive(const FileSystemItem& item) const {
        if (item.mIsDirectory) {
            bool open = ImGui::TreeNodeEx(item.mName.c_str(), ImGuiTreeNodeFlags_OpenOnArrow);
            if (open) {
                for (const auto& child : item.mChildren) {
                    RenderImGuiTreeRecursive(child);
                }
                ImGui::TreePop();
            }
        } else {
            ImGui::TreeNodeEx(item.mName.c_str(), ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen);
        }
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
    static FileSystemItem assetStructure;
public:
    static const FileSystemItem &getAssetStructure();

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

    static void initialise() {
        refreshAssets();
    }

    static void refreshAssets() {
        assetStructure = FileSystemItem::buildFileStructure("..\\assets");
    }
};


