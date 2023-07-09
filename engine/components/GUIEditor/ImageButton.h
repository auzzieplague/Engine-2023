#pragma once
#include <string>
#include <functional>
#include <imgui/imgui.h>

class Scene;
struct ImageButton {
    std::string title;
    std::function<void()> onClick;
    std::function<void(int)> onDrop;
    ImTextureID textureID{};

    ImVec2 uvMin; // Top-left UV coordinate
    ImVec2 uvMax; // Bottom-right UV coordinate
    ImVec2 size;  // Size of the button

    int dropFrameCount = -1;

    void drawButton(Scene *scene);
};
