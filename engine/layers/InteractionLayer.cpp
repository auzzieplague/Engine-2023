#pragma once

#include "InteractionLayer.h"

void InteractionLayer::onAttach(Scene *scene) {
    // bind this input to inputInstance
    Debug::show("[>] Interaction Attached");
    this->input = new Input(scene->currentWindow->glRef());
    this->iconAtlas = this->api->loadTexture(AssetManager::getRelativePath("icons", "editor.png"));
}

void InteractionLayer::processInput(Scene *scene) {

    this->currentComponent = scene->selectedComponent;

    float speed = 10; // travel speed
    float movement = speed / scene->currentFrameRate;

    if (Input::isKeyPressed(GLFW_KEY_R)) {
        Debug::resetIteration();
    }

    processCameraInput(scene, movement);

    if (this->currentComponent && this->currentComponent->getType() == ObjectType::OT_Model) {
        if (dynamic_cast<Model *>(currentComponent)->isDynamic()) {
            handleCharacterKeysWithPhysics();
            return;
        }
    }

    handleCharacterKeys(movement);

}

void InteractionLayer::handleCharacterKeys(float movement) {
    if (Input::isKeyPressed(GLFW_KEY_UP) | Input::isKeyPressed(GLFW_KEY_KP_8)) {
        glm::vec3 pos = currentComponent->getLocalPosition();
        pos.y += movement / 2;
        currentComponent->setPosition(pos);

    };
    if (Input::isKeyPressed(GLFW_KEY_DOWN) | Input::isKeyPressed(GLFW_KEY_KP_2)) {
        glm::vec3 pos = currentComponent->getLocalPosition();
        pos.y -= movement / 2;
        currentComponent->setPosition(pos);

    };
    if (Input::isKeyPressed(GLFW_KEY_PAGE_DOWN) | Input::isKeyPressed(GLFW_KEY_KP_ADD)) {
        glm::vec3 pos = currentComponent->getLocalPosition();
        pos.z += movement / 2;
        currentComponent->setPosition(pos);

    };
    if (Input::isKeyPressed(GLFW_KEY_PAGE_UP) | Input::isKeyPressed(GLFW_KEY_KP_SUBTRACT)) {
        glm::vec3 pos = currentComponent->getLocalPosition();
        pos.z -= movement / 2;
        currentComponent->setPosition(pos);
    };
    if (Input::isKeyPressed(GLFW_KEY_RIGHT) | Input::isKeyPressed(GLFW_KEY_KP_6)) {
        glm::vec3 pos = currentComponent->getLocalPosition();
        pos.x += movement / 2;
        currentComponent->setPosition(pos);
    };
    if (Input::isKeyPressed(GLFW_KEY_LEFT) | Input::isKeyPressed(GLFW_KEY_KP_4)) {
        glm::vec3 pos = currentComponent->getLocalPosition();
        pos.x -= movement / 2;
        currentComponent->setPosition(pos);
    };

    if (Input::isKeyPressed(GLFW_KEY_U)) {
        currentComponent->rotateX(0.1);
    }

    if (Input::isKeyPressed(GLFW_KEY_I)) {
        currentComponent->rotateY(0.1);
    }

    if (Input::isKeyPressed(GLFW_KEY_O)) {
        currentComponent->rotateZ(0.1);
    }

    if (Input::isKeyPressed(GLFW_KEY_R)) {
        currentComponent->roll(0.1);
    }

    if (Input::isKeyPressed(GLFW_KEY_P)) {
        currentComponent->pitch(0.1);
    }

    if (Input::isKeyPressed(GLFW_KEY_Y)) {
        currentComponent->yaw(0.1);
    }

    float scaleSpeed = 0.001;
    if (Input::isKeyPressed(GLFW_KEY_V)) {
        currentComponent->scale(1 + scaleSpeed);
    }

    if (Input::isKeyPressed(GLFW_KEY_B)) {
        currentComponent->scale(1 - scaleSpeed);
    }
}

void InteractionLayer::handleCharacterKeysWithPhysics() {
    float force = .01; // the force to apply to objects
    Model *model = dynamic_cast<Model *>(currentComponent);
    if (Input::isKeyPressed(GLFW_KEY_I) | Input::isKeyPressed(GLFW_KEY_KP_8)) {
        model->applyImpulse(glm::vec3{0, 0, -force});
    }
    if (Input::isKeyPressed(GLFW_KEY_K) | Input::isKeyPressed(GLFW_KEY_KP_2)) {

        model->applyImpulse(glm::vec3{0, 0, +force});
    }
    if (Input::isKeyPressed(GLFW_KEY_L) | Input::isKeyPressed(GLFW_KEY_KP_ADD)) {
        model->applyImpulse(glm::vec3{0, force + .2, 0});
    }
    if (Input::isKeyPressed(GLFW_KEY_O) | Input::isKeyPressed(GLFW_KEY_KP_SUBTRACT)) {
        model->applyImpulse(glm::vec3{0, -force, 0});
    }
    if (Input::isKeyPressed(GLFW_KEY_PERIOD) | Input::isKeyPressed(GLFW_KEY_KP_6)) {
        model->applyImpulse(glm::vec3{force, 0, 0});
    }
    if (Input::isKeyPressed(GLFW_KEY_COMMA) | Input::isKeyPressed(GLFW_KEY_KP_4)) {
        model->applyImpulse(glm::vec3{-force, 0, 0});
    }
}

void InteractionLayer::processCameraInput(Scene *scene, float movement) {
    /// todo add mappings for camera keys, for now just use wasd
    float sensitivity = 1;

    if (Input::isKeyPressed(GLFW_KEY_W)) {
        scene->currentCamera->moveForward(movement);
    };

    if (Input::isKeyPressed(GLFW_KEY_S)) {
        scene->currentCamera->moveBackward(movement);
    };

    if (Input::isKeyPressed(GLFW_KEY_A)) {
        scene->currentCamera->moveLeft(movement);
    };

    if (Input::isKeyPressed(GLFW_KEY_D)) {
        scene->currentCamera->moveRight(movement);
    };

    if (Input::isKeyPressed(GLFW_KEY_SPACE)) {
        scene->currentCamera->moveUp(movement);
    };

    if (Input::isKeyPressed(GLFW_KEY_X)) {
        scene->currentCamera->moveDown(movement);
    };

    if (Input::isRightMouseDragging()) {
        glm::vec2 delta = Input::getDragDistance();
        scene->currentCamera->rotate(delta.x * sensitivity, -delta.y * sensitivity, true);
    }
};

void InteractionLayer::appendToGui(Scene *scene) {
    selectedComponentGui(scene->selectedComponent);
    sceneComponentsGui(scene);
    toolboxGui(scene);
}

void InteractionLayer::transformGui(std::string text, Transform transform) {
    if (ImGui::CollapsingHeader(text.c_str())) {
        ImGui::PushItemWidth(80);
        {
            ImGui::DragFloat("lpx", &transform.mPosition.x, 0.5f);
            ImGui::SameLine();
            ImGui::DragFloat("lpy", &transform.mPosition.y, 0.5f);
            ImGui::SameLine();
            ImGui::DragFloat("lpz", &transform.mPosition.z, 0.5f);
        }
        {
            ImGui::DragFloat("lrx", &transform.mRotation.x, 0.5f);
            ImGui::SameLine();
            ImGui::DragFloat("lry", &transform.mRotation.y, 0.5f);
            ImGui::SameLine();
            ImGui::DragFloat("lrz", &transform.mRotation.z, 0.5f);
        }
        {
            ImGui::DragFloat("lsx", &transform.mScale.x, 0.5f);
            ImGui::SameLine();
            ImGui::DragFloat("lsy", &transform.mScale.y, 0.5f);
            ImGui::SameLine();
            ImGui::DragFloat("lsz", &transform.mScale.z, 0.5f);
        }
    }
}

void InteractionLayer::componentTreeGui(Component *component) {
    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    bool open = ImGui::TreeNode(component->getName().c_str());
    ImGui::PopStyleColor();

    if (open) {
        ImGui::SameLine();
        ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.5f, 0.5f));
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4.0f, 2.0f));


        if (ImGui::Button("Select")) {
            this->currentScene->selectedComponent = component;
        }

        ImGui::PopStyleVar(2);

        for (auto child: component->childComponents) {
            componentTreeGui(child);
        }
        ImGui::TreePop();
    }
}

void InteractionLayer::sceneComponentsGui(Scene *scene) {
    ImGui::Begin("Scene Layout");

    // Iterate over the component list in the scene
    for (auto component: scene->componentList) {
        componentTreeGui(component);
    }

    ImGui::End();
}

void InteractionLayer::selectedComponentGui(Component *component) {

    ImGui::Begin("Selected Item");

    if (!component) {
        ImGui::End();
    }

    if (component->parentComponent && ImGui::Button("Select Parent")) {
            currentScene->selectedComponent = component->parentComponent;
    }

    ImGui::InputText("Component Name", &component->objectName[0], component->objectName.size() + 1);

    if (!component->parentComponent) {
        transformGui("Transform", component->localTransform);
    }

    ImGui::End();
}

void InteractionLayer::toolboxGui(Scene *scene) {
    // scene might contain editor mode / play mode

    ImGui::Begin("Icons Item");
    ImageButton button;
    button.uvMin = ImVec2(0.0f, 0.0f);
    button.uvMax = ImVec2(0.25f, 0.25f);
    button.size = ImVec2(50, 50);
    button.title = "Add Sphere";
    button.onClick = [scene]() {
        auto *model = Model::createWithGeometry(Geometry::ShapeType::Sphere);
        scene->addComponent(model);

        if (scene->selectedComponent) {
            model->setPosition(scene->selectedComponent->getLocalPosition() + glm::vec3(0.1));
        }

        Material material;
//        material.loadFromAsset("defaults", "default.png"); // couldnt select this material
        material.loadFromAsset("mats_ground", "gray-bricks1");
        model->setMaterial(material);
        scene->selectedComponent = model;
    };
    button.onDrop = [](int frameCount) {
        std::cout << "Not functioning :[ " << frameCount << '\n';
    };
    button.textureID = reinterpret_cast<ImTextureID>(this->iconAtlas);
    button.Render(scene);

    ImGui::End();
}