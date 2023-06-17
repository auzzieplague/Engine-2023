#pragma once

#include "InteractionLayer.h"

void InteractionLayer::onAttach(Scene *scene) {
    // bind this input to inputInstance
    Debug::show("[>] Interaction Attached");
    this->input = new Input(scene->currentWindow->glRef());
}

void InteractionLayer::processInput(Scene *scene) {

    float speed = 10; // travel speed
    float movement = speed / scene->currentFrameRate;

    processCameraInput(scene, movement);

    if (selectedModel) {
        if (selectedModel->isDynamic()) {
            handleCharacterKeysWithPhysics();
        } else {
            handleCharacterKeys(movement);
        }
    }

    if (input->isKeyPressed(GLFW_KEY_R)) {
        Debug::resetIteration();
    };
}

void InteractionLayer::handleCharacterKeys(float movement) {
    if (input->isKeyPressed(GLFW_KEY_UP) | input->isKeyPressed(GLFW_KEY_KP_8)) {
        glm::vec3 pos = selectedModel->getWorldPosition();
        pos.y += movement / 2;
        selectedModel->setWorldPosition(pos);

    };
    if (input->isKeyPressed(GLFW_KEY_DOWN) | input->isKeyPressed(GLFW_KEY_KP_2)) {
        glm::vec3 pos = selectedModel->getWorldPosition();
        pos.y -= movement / 2;
        selectedModel->setWorldPosition(pos);

    };
    if (input->isKeyPressed(GLFW_KEY_PAGE_DOWN) | input->isKeyPressed(GLFW_KEY_KP_ADD)) {
        glm::vec3 pos = selectedModel->getWorldPosition();
        pos.z += movement / 2;
        selectedModel->setWorldPosition(pos);

    };
    if (input->isKeyPressed(GLFW_KEY_PAGE_UP) | input->isKeyPressed(GLFW_KEY_KP_SUBTRACT)) {
        glm::vec3 pos = selectedModel->getWorldPosition();
        pos.z -= movement / 2;
        selectedModel->setWorldPosition(pos);
    };
    if (input->isKeyPressed(GLFW_KEY_RIGHT) | input->isKeyPressed(GLFW_KEY_KP_6)) {
        glm::vec3 pos = selectedModel->getWorldPosition();
        pos.x += movement / 2;
        selectedModel->setWorldPosition(pos);
    };
    if (input->isKeyPressed(GLFW_KEY_LEFT) | input->isKeyPressed(GLFW_KEY_KP_4)) {
        glm::vec3 pos = selectedModel->getWorldPosition();
        pos.x -= movement / 2;
        selectedModel->setWorldPosition(pos);
    };

    if (input->isKeyPressed(GLFW_KEY_U)) {
        selectedModel->rotateX(0.1);
    }

    if (input->isKeyPressed(GLFW_KEY_I)) {
        selectedModel->rotateY(0.1);
    }

    if (input->isKeyPressed(GLFW_KEY_O)) {
        selectedModel->rotateZ(0.1);
    }

    if (input->isKeyPressed(GLFW_KEY_R)) {
        selectedModel->roll(0.1);
    }

    if (input->isKeyPressed(GLFW_KEY_P)) {
        selectedModel->pitch(0.1);
    }

    if (input->isKeyPressed(GLFW_KEY_Y)) {
        selectedModel->yaw(0.1);
    }
}

void InteractionLayer::handleCharacterKeysWithPhysics() {
    float force = .01; // the force to apply to objects

    if (input->isKeyPressed(GLFW_KEY_I) | input->isKeyPressed(GLFW_KEY_KP_8)) {
        selectedModel->applyImpulse(glm::vec3{0, 0, -force});
    }
    if (input->isKeyPressed(GLFW_KEY_K) | input->isKeyPressed(GLFW_KEY_KP_2)) {

        selectedModel->applyImpulse(glm::vec3{0, 0, +force});
    }
    if (input->isKeyPressed(GLFW_KEY_L) | input->isKeyPressed(GLFW_KEY_KP_ADD)) {
        selectedModel->applyImpulse(glm::vec3{0, force+.2, 0});
    }
    if (input->isKeyPressed(GLFW_KEY_O) | input->isKeyPressed(GLFW_KEY_KP_SUBTRACT)) {
        selectedModel->applyImpulse(glm::vec3{0, -force, 0});
    }
    if (input->isKeyPressed(GLFW_KEY_PERIOD) | input->isKeyPressed(GLFW_KEY_KP_6)) {
        selectedModel->applyImpulse(glm::vec3{force, 0, 0});
    }
    if (input->isKeyPressed(GLFW_KEY_COMMA) | input->isKeyPressed(GLFW_KEY_KP_4)) {
        selectedModel->applyImpulse(glm::vec3{-force, 0, 0});
    }
}

void InteractionLayer::processCameraInput(Scene *scene, float movement) {
    /// todo add mappings for camera keys, for now just use wasd
    float sensitivity = 1;

    if (input->isKeyPressed(GLFW_KEY_W)) {
        scene->currentCamera->moveForward(movement);
    };

    if (input->isKeyPressed(GLFW_KEY_S)) {
        scene->currentCamera->moveBackward(movement);
    };

    if (input->isKeyPressed(GLFW_KEY_A)) {
        scene->currentCamera->moveLeft(movement);
    };

    if (input->isKeyPressed(GLFW_KEY_D)) {
        scene->currentCamera->moveRight(movement);
    };

    if (input->isKeyPressed(GLFW_KEY_SPACE)) {
        scene->currentCamera->moveUp(movement);
    };

    if (input->isKeyPressed(GLFW_KEY_X)) {
        scene->currentCamera->moveDown(movement);
    };

    if (Input::isRightMouseDragging()) {
        glm::vec2 delta = Input::getDragDistance();
        scene->currentCamera->rotate(delta.x * sensitivity, -delta.y * sensitivity, true);
    }
};


void InteractionLayer::selectedObjectGui(Scene *scene) {
    ImGui::Begin("Selected Item");
    if (scene->selectedComponent) {
        if (ImGui::SmallButton("Move Forward")) {
//            scene->selectedComponent->moveForward(1);
        }
//
//        Transform transform = scene->selectedComponent->getLocalTransform();
//        ImGui::PushItemWidth(80);
//        {
//            ImGui::DragFloat("px", &scene->selectedComponent->position.x, 0.5f);
//            ImGui::SameLine();
//            ImGui::DragFloat("py", &scene->selectedComponent->position.y, 0.5f);
//            ImGui::SameLine();
//            ImGui::DragFloat("pz", &scene->selectedComponent->position.z, 0.5f);
//        }
//        {
//            ImGui::DragFloat("rx", &scene->selectedComponent->rotation.x, 0.5f);
//            ImGui::SameLine();
//            ImGui::DragFloat("ry", &scene->selectedComponent->rotation.y, 0.5f);
//            ImGui::SameLine();
//            ImGui::DragFloat("rz", &scene->selectedComponent->rotation.z, 0.5f);
//        }
//        {
//            ImGui::DragFloat("sx", &scene->selectedComponent->scale.x, 0.5f);
//            ImGui::SameLine();
//            ImGui::DragFloat("sy", &scene->selectedComponent->scale.y, 0.5f);
//            ImGui::SameLine();
//            ImGui::DragFloat("sz", &scene->selectedComponent->scale.z, 0.5f);
//        }
//
//        ImGui::Checkbox("Dynamic", &scene->selectedComponent->isDynamic);

        ImGui::PopItemWidth();
    }
    ImGui::End();
}

void InteractionLayer::appendToGui(Scene *scene) {
    selectedObjectGui(scene);
}
