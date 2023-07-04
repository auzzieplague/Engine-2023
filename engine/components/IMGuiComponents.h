
#pragma once
#include "../../vendor/imgui/imgui.h"
#include "../../vendor/imgui/imgui_impl_glfw.h"
#include "../../vendor/imgui/imgui_impl_opengl3.h"
#include "../../vendor/ImGuizmo/ImGuizmo.h"
#include <glm/gtc/type_ptr.hpp>
#include "../Engine.h"
#include <functional>
#include <string>

struct ImageButton
{
    ImVec2 uvMin; // Top-left UV coordinate
    ImVec2 uvMax; // Bottom-right UV coordinate
    ImVec2 size;  // Size of the button
    std::string title;
    std::function<void()> onClick;
    std::function<void(int)> onDrop;
    ImTextureID textureID;
    int dropFrameCount = -1;
    void Render(Scene *scene);
};

class IMGuiHelper {
public:
    static void buildTreeFromFileList(const std::vector<std::string>& fileList);

    static void makePushButton(const std::string& text, const std::function<void()>& onClick);
};

