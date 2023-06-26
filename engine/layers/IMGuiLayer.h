#ifndef ONION_IMGUI_LAYER_H
#define ONION_IMGUI_LAYER_H

#pragma once
#define IMGUI_IMPL_OPENGL_LOADER_GLAD

#include "Layer.h"
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

class IMGuiLayer :
        public Layer
{
    unsigned int iconAtlas;

    uint32_t getFrequency() override { return 10; };

    ImGuizmo::OPERATION gizmoMode = ImGuizmo::TRANSLATE;

    // requires opengl to be initialised first
    void onAttach(Scene* scene);
    void onDetach(Scene* scene);

    void appendToGui(Scene* scene);
    void drawGizmos(Scene* scene);

    void beforeUpdate(Scene*);
    void update(Scene*);
    void afterUpdate(Scene*);

    void beforeRender(Scene*);
    void render(Scene*);
    void afterRender(Scene*);

    void processInput(Scene* scene);

    void buildDockSpace(Scene* scene);

    void loadAssets(Scene *scene);

    void drawIcons(Scene *scene);
};



#endif //ONION_IMGUI_LAYER_H
