
#include "IMGuiComponents.h"


void IMGuiHelper::buildTreeFromFileList(const std::vector<std::string> &fileList) {
    static int nodeID = 0;

    for (const auto& file : fileList) {
        bool isDirectory = file.find("(Directory)") != std::string::npos;
        std::string nodeName = isDirectory ? file.substr(0, file.length() - 11) : file;

        ImGui::PushID(nodeID++);

        if (isDirectory) {
            bool open = ImGui::TreeNodeEx(nodeName.c_str(), ImGuiTreeNodeFlags_OpenOnArrow);
            if (open) {
                // Recursively build the tree for subdirectories
                buildTreeFromFileList(fileList);
                ImGui::TreePop();
            }
        } else {
            ImGui::TreeNodeEx(nodeName.c_str(), ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen);
        }

        ImGui::PopID();
    }
}

void ImageButton::Render(Scene *scene) {

    if (ImGui::ImageButton(textureID, size, uvMin, uvMax))
    {
        if (onClick)
        {
            onClick();
        }
    }

    ImGui::SameLine();

    if (ImGui::IsItemHovered())
    {
        ImGui::SetTooltip("%s", title.c_str());
    }


    if (ImGui::BeginDragDropSource())
    {
        ImGui::SetDragDropPayload("BUTTON_PAYLOAD", this, sizeof(ImageButton));
        ImGui::Text("Drag and drop me!");

        ImGui::EndDragDropSource();
    }

    if (ImGui::BeginDragDropTarget()) {
        dropFrameCount = ImGui::GetFrameCount(); // Store the current frame count
        if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("BUTTON_PAYLOAD")) {
        }
        ImGui::EndDragDropTarget();
    }
}
