
#include "IMGuiComponents.h"

void IMGuiHelper::buildTreeFromFileList(const std::vector<std::string> &fileList) {
        for (const auto& file : fileList) {
            std::vector<std::string> pathComponents;
            std::string tempFile = file;

            // Split the path into individual components
            while (!tempFile.empty()) {
                auto pos = tempFile.find('/');
                if (pos != std::string::npos) {
                    std::string component = tempFile.substr(0, pos);
                    pathComponents.push_back(component);
                    tempFile = tempFile.substr(pos + 1);
                } else {
                    pathComponents.push_back(tempFile);
                    break;
                }
            }

            // Build the nested tree structure
            std::string nodeLabel;
            for (const auto& component : pathComponents) {
                nodeLabel += component;
                bool isDirectory = (component.find("(Directory)") != std::string::npos);
                ImGuiTreeNodeFlags nodeFlags = (isDirectory) ? ImGuiTreeNodeFlags_OpenOnArrow : ImGuiTreeNodeFlags_Leaf;
                if (!ImGui::TreeNodeEx(nodeLabel.c_str(), nodeFlags)) {
                    break;
                }
                ImGui::TreePop();
                nodeLabel += "/";
            }
        }
}

void IMGuiHelper::makePushButton(const std::string& text, const std::function<void()> &onClick) {
    ImGui::SameLine();
    ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.5f, 0.5f));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4.0f, 2.0f));

    if (ImGui::Button(text.c_str())) {
        onClick();
    }

    ImGui::PopStyleVar(2);
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
