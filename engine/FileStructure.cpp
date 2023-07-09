
#include "FileStructure.h"


FileStructure::FileStructure(const std::string &name, bool isDirectory) {
    mPath = name;
    mIsDirectory = isDirectory;
    mName = ExtractFilename(name);
    //get file extension and set isLoadable

    auto extension = getFileExtension(mName);
    if (extension == "obj") {
        isLoadable = true;
    }
}

void FileStructure::AddChild(const FileStructure &child) {
    mChildren.push_back(child);
}

void FileStructure::RenderImGuiTree() const {
    RenderImGuiTreeRecursive(*this);
}

std::string FileStructure::getFileExtension(const std::string &fileName) {
    size_t dotIndex = fileName.find_last_of('.');
    if (dotIndex != std::string::npos && dotIndex < fileName.length() - 1) {
        return fileName.substr(dotIndex + 1);
    }
    return "";  // No file extension found
}

FileStructure FileStructure::buildFileStructure(const std::string &path) {
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

void FileStructure::RenderImGuiTreeRecursive(const FileStructure &item) const {
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
    if (item.isLoadable) {
        ImGui::SameLine();
        ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.5f, 0.5f));
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4.0f, 2.0f));
        if (ImGui::Button("Load")) {
            // todo add item into a list of items to be loaded on a queue to be picked up by a layer.
            Debug::show("load model");
        }
        ImGui::PopStyleVar(2);
    }
}

std::string FileStructure::ExtractFilename(const std::string &path) {
    size_t lastSlashIndex = path.find_last_of("/\\");
    if (lastSlashIndex != std::string::npos) {
        return path.substr(lastSlashIndex + 1);
    }
    return path;
}
