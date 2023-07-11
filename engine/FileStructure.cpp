#include "FileStructure.h"

FileStructure::FileStructure(const std::string &name, const std::string &fullPath, bool isDirectory) {
    mFileName = name;
    mFullPath = fullPath;
    mIsDirectory = isDirectory;
    mName = ExtractFilename(name);
    // get file extension and set isLoadable

    auto extension = getFileExtension(mName);
    if (extension == "obj") {
        isLoadable = true;
    }
}

void FileStructure::AddChild(const FileStructure &child) {
    mChildren.push_back(child);
}

void FileStructure::RenderImGuiTree() const {
//    RenderImGuiTreeRecursive(*this);
}

std::string FileStructure::getFileExtension(const std::string &fileName) {
    size_t dotIndex = fileName.find_last_of('.');
    if (dotIndex != std::string::npos && dotIndex < fileName.length() - 1) {
        return fileName.substr(dotIndex + 1);
    }
    return "";  // No file extension found
}

FileStructure FileStructure::buildFileStructure(const std::string &path) {
    FileStructure root(path,path, true);

    for (const auto &entry: std::filesystem::directory_iterator(path)) {
        std::string name = entry.path().filename().string();
        bool isDirectory = std::filesystem::is_directory(entry.path());

        if (isDirectory) {
            FileStructure subdirectory = buildFileStructure(entry.path().string());
            root.AddChild(subdirectory);
        } else {
            root.AddChild(FileStructure(name,entry.path().string()));
        }
    }

    return root;
}


std::string FileStructure::ExtractFilename(const std::string &path) {
    size_t lastSlashIndex = path.find_last_of("/\\");
    if (lastSlashIndex != std::string::npos) {
        return path.substr(lastSlashIndex + 1);
    }
    return path;
}
