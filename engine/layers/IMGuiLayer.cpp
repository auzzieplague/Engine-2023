#include "IMGuiLayer.h"

// note : require openGL attached first
void IMGuiLayer::onAttach(Scene *scene) {
    const char *glsl_version = "#version 130";
    gladLoadGL();

    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(scene->currentWindow->glRef(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    Debug::show("[>] IMGUI Attached");

};

void IMGuiLayer::beforeUpdate(Scene *scene) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    buildDockSpace(scene);
};

void IMGuiLayer::buildDockSpace(Scene *scene) {
    static bool showDockSpace = true;
    static ImGuiDockNodeFlags dockSpaceFlags = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                    ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus |
                    ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(scene->currentWindow->getWidth(), scene->currentWindow->getHeight()));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    ImGui::Begin("MyDockSpace", &showDockSpace, window_flags);
    {
        ImGui::DockSpace(ImGui::GetID("MyDockSpace"), ImVec2(0.0f, 0.0f), dockSpaceFlags);
        ImGui::PopStyleVar();
    }
    ImGui::End();
}

void IMGuiLayer::update(Scene *scene) {
    static bool alreadyCapturedKeyPress = false;
//
//    if (Input::keyDown[GLFW_KEY_TAB]) {
//        if (alreadyCapturedKeyPress == false) {
//            alreadyCapturedKeyPress = true;
//            switch (gizmoMode) {
//                case ImGuizmo::TRANSLATE:
//                    gizmoMode = ImGuizmo::ROTATE;
//                    break;
//                case ImGuizmo::ROTATE:
//                    gizmoMode = ImGuizmo::SCALE;
//                    break;
////                case ImGuizmo::SCALE:
////                    gizmoMode = ImGuizmo::UNIVERSAL;
////                    break;
//                default:
//                    gizmoMode = ImGuizmo::TRANSLATE;
//            }
//        }
//    } else {
//        alreadyCapturedKeyPress = false;
//    }
};

void IMGuiLayer::afterUpdate(Scene *scene) {};

void IMGuiLayer::beforeRender(Scene *) {}

void IMGuiLayer::appendToGui(Scene *scene) {}

void IMGuiLayer::drawGizmos(Scene *scene) {
//    if (!scene->selectedComponent) return;
//    ImGui::GetIO().WantCaptureMouse = false;
//    ImGuiIO &io = ImGui::GetIO();
//
//    static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::WORLD);
//
//    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
//    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
//                    ImGuiWindowFlags_NoMove;
//    window_flags |=
//            ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;
//    ImGui::SetNextWindowPos(ImVec2(0, 0));
//    ImGui::SetNextWindowSize(ImVec2(scene->window->width, scene->window->height));
//    bool show_viewport = true;
//    ImGui::Begin("GizmoViewport", &show_viewport, window_flags);
//
//    ImGuizmo::BeginFrame();
//    ImGuizmo::Enable(true);
//    ImGuizmo::SetOrthographic(false);
//    ImGuizmo::SetDrawlist();
//
//    ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
//
//    /// needed couple or workarounds to be able to use the gui widgets
//    /// position needs to be set using setter to allow for dynamic targetPosition overrides
//    /// rotation extracted from a matrix doesn't work correctly, might need converting back to Euler angles and setting manually (gimbal lock issues)
//    float matrix[16];
//    ImGuizmo::RecomposeMatrixFromComponents(glm::value_ptr(scene->selectedComponent->position),
//                                            glm::value_ptr(scene->selectedComponent->rotation),
//                                            glm::value_ptr(scene->selectedComponent->scale), matrix);
//    ImGuizmo::Manipulate(glm::value_ptr(scene->activeCamera->viewMatrix),
//                         glm::value_ptr(scene->config.projectionMatrix), gizmoMode, mCurrentGizmoMode, matrix, NULL,
//                         NULL, NULL, NULL);
//    glm::vec3 position;
//    ImGuizmo::DecomposeMatrixToComponents(matrix, glm::value_ptr(position),
//                                          glm::value_ptr(scene->selectedComponent->rotation),
//                                          glm::value_ptr(scene->selectedComponent->scale));
//    scene->selectedComponent->setPosition(position);
//    ImGui::End();
}

void IMGuiLayer::render(Scene *scene) {
//    if (scene->config.editMode) {
//        drawGizmos(scene);
//    }
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void IMGuiLayer::afterRender(Scene *scene) {
}


void IMGuiLayer::processInput(Scene *scene) {
    ImGuiIO &io = ImGui::GetIO();
    // if were over a IMGUI window stop mouse presses from flowing into other layers
    if (io.WantCaptureMouse) {
        // need to exclude viewport
//        scene->input->triggeredEvents.mouseDown = false;

    }
}

void IMGuiLayer::onDetach(Scene *scene) {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}




