
#include "../../core/Base.h"
#include <filesystem>
#include <imgui.h>

namespace fs = std::filesystem;

class FileStructure {
protected:
    friend class AssetManager;

    std::string mPath;
    std::string mName;;
    bool isLoadable = false;
    bool mIsDirectory = false;
    std::vector<FileStructure> mChildren;

    static FileStructure buildFileStructure(const std::string &path);

    void RenderImGuiTreeRecursive(const FileStructure &item) const;


    std::string ExtractFilename(const std::string &path);

public:
    explicit FileStructure(const std::string &name, bool isDirectory = false);

    FileStructure() = default;

    void AddChild(const FileStructure &child);

    void RenderImGuiTree() const;

    std::string getFileExtension(const std::string &fileName);

};
