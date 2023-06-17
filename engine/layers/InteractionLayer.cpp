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

        ImGui::Text("Local Transform");
        ImGui::PushItemWidth(80);
        {
            ImGui::DragFloat("lpx", &scene->selectedComponent->localTransform.mPosition.x, 0.5f);
            ImGui::SameLine();
            ImGui::DragFloat("lpy", &scene->selectedComponent->localTransform.mPosition.y, 0.5f);
            ImGui::SameLine();
            ImGui::DragFloat("lpz", &scene->selectedComponent->localTransform.mPosition.z, 0.5f);
        }
        {
            ImGui::DragFloat("lrx", &scene->selectedComponent->localTransform.mRotation.x, 0.5f);
            ImGui::SameLine();
            ImGui::DragFloat("lry", &scene->selectedComponent->localTransform.mRotation.y, 0.5f);
            ImGui::SameLine();
            ImGui::DragFloat("lrz", &scene->selectedComponent->localTransform.mRotation.z, 0.5f);
        }
        {
            ImGui::DragFloat("lsx", &scene->selectedComponent->localTransform.mScale.x, 0.5f);
            ImGui::SameLine();
            ImGui::DragFloat("lsy", &scene->selectedComponent->localTransform.mScale.y, 0.5f);
            ImGui::SameLine();
            ImGui::DragFloat("lsz", &scene->selectedComponent->localTransform.mScale.z, 0.5f);
        }

        ImGui::Text("World Transform");
        ImGui::PushItemWidth(80);
        {
            ImGui::DragFloat("wpx", &scene->selectedComponent->worldTransform.mPosition.x, 0.5f);
            ImGui::SameLine();
            ImGui::DragFloat("wpy", &scene->selectedComponent->worldTransform.mPosition.y, 0.5f);
            ImGui::SameLine();
            ImGui::DragFloat("wpz", &scene->selectedComponent->worldTransform.mPosition.z, 0.5f);
        }
        {
            ImGui::DragFloat("wrx", &scene->selectedComponent->worldTransform.mRotation.x, 0.5f);
            ImGui::SameLine();
            ImGui::DragFloat("wry", &scene->selectedComponent->worldTransform.mRotation.y, 0.5f);
            ImGui::SameLine();
            ImGui::DragFloat("wrz", &scene->selectedComponent->worldTransform.mRotation.z, 0.5f);
        }
        {
            ImGui::DragFloat("wsx", &scene->selectedComponent->worldTransform.mScale.x, 0.5f);
            ImGui::SameLine();
            ImGui::DragFloat("wsy", &scene->selectedComponent->worldTransform.mScale.y, 0.5f);
            ImGui::SameLine();
            ImGui::DragFloat("wsz", &scene->selectedComponent->worldTransform.mScale.z, 0.5f);
        }
        ImGui::PopItemWidth();

        scene->selectedComponent->updateFinalTransform();
    }
    ImGui::End();
}

void InteractionLayer::appendToGui(Scene *scene) {
    selectedObjectGui(scene);
}
