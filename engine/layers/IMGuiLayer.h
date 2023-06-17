#ifndef ONION_IMGUI_LAYER_H
#define ONION_IMGUI_LAYER_H

#pragma once
#define IMGUI_IMPL_OPENGL_LOADER_GLAD

#include "Layer.h"
#include "../../vendor/imgui/imgui.h"
#include "../../vendor/imgui/imgui_impl_glfw.h"
#include "../../vendor/imgui/imgui_impl_opengl3.h"
#include "../../vendor/ImGuizmo/ImGuizmo.h"
#include "../Engine.h"

class IMGuiLayer :
        public Layer
{

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
};



#endif //ONION_IMGUI_LAYER_H
