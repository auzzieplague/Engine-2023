
#pragma once

#include "../../vendor/imgui/imgui.h"
#include "../../vendor/imgui/imgui_impl_glfw.h"
#include "../../vendor/imgui/imgui_impl_opengl3.h"
#include "../../vendor/ImGuizmo/ImGuizmo.h"
#include <glm/gtc/type_ptr.hpp>
#include "../Engine.h"
#include <functional>
#include <string>
#include <imgui/imgui.h>


class IMGuiHelper {
public:
    static void buildTreeFromFileList(const std::vector<std::string> &fileList);

    static void makePushButton(const std::string &text, const std::function<void()> &onClick);
};

