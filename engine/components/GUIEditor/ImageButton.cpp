#include "ImageButton.h"

void ImageButton::drawButton(Scene *scene) {

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
