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
    static bool keyReleased = true;

    if (!keyReleased && !Input::isKeyPressed(GLFW_KEY_TAB)) {
        keyReleased = true;
    }

    if (Input::isKeyPressed(GLFW_KEY_TAB) && keyReleased) {
        keyReleased = false;
        switch (gizmoMode) {
            case ImGuizmo::TRANSLATE:
                gizmoMode = ImGuizmo::ROTATE;;
                break;
            case ImGuizmo::ROTATE:
                gizmoMode = ImGuizmo::SCALE;
                break;
            default:
                gizmoMode = ImGuizmo::TRANSLATE;
        }
    }
}

void IMGuiLayer::drawGizmos(Scene *scene) {
    if (!scene->selectedComponent) return;
    if (scene->moveObjectWithMouse) return;

    // child manipulation not supported atm
//    if (scene->selectedComponent->parentComponent) return;

    scene->selectedComponent->pause();

    ImGui::GetIO().WantCaptureMouse = false;
    ImGuiIO &io = ImGui::GetIO();

    static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::WORLD); // currently, using mixed

    ImGuiWindowFlags window_flags =
            ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse
            | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus
            | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(scene->currentWindow->getWidth(), scene->currentWindow->getHeight()));
    bool show_viewport = true;
    ImGui::Begin("GizmoViewport", &show_viewport, window_flags);

    ImGuizmo::BeginFrame();
    ImGuizmo::Enable(true);
    ImGuizmo::SetOrthographic(false);
    ImGuizmo::SetDrawlist();

    ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);

    auto parent = scene->selectedComponent->parentComponent;

    auto *selectedTransform = &scene->selectedComponent->localTransform;

    float matrix[16];
    float delta[16];
    ImGuizmo::RecomposeMatrixFromComponents(glm::value_ptr(selectedTransform->mPosition),
                                            glm::value_ptr(selectedTransform->mRotation),
                                            glm::value_ptr(selectedTransform->mScale), matrix);

    ImGuizmo::Manipulate(glm::value_ptr(scene->currentCamera->mViewMatrix),
                         glm::value_ptr(scene->currentCamera->mProjectionMatrix), gizmoMode, mCurrentGizmoMode, matrix,
                         delta,
                         NULL, NULL, NULL);

    glm::vec3 position, rotation, scale, dPosition, dRotation, dScale;

    ImGuizmo::DecomposeMatrixToComponents(matrix, glm::value_ptr(position),
                                          glm::value_ptr(rotation),
                                          glm::value_ptr(scale));

    ImGuizmo::DecomposeMatrixToComponents(delta, glm::value_ptr(dPosition),
                                          glm::value_ptr(dRotation),
                                          glm::value_ptr(dScale));

    // if there are any changes then we'll need to consider physx

    if (scene->selectedComponent->parentComponent) {

    } else {
        scene->selectedComponent->setPosition(position);
        scene->selectedComponent->rotate(dRotation);
        scene->selectedComponent->scale(dScale);
    }

    ImGui::End();
}

void IMGuiLayer::render(Scene *scene) {
    ImGui::ShowDemoWindow();
    drawGizmos(scene);
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

