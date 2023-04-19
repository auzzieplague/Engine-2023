#pragma once

#include "InteractionLayer.h"


void InteractionLayer::onAttach(Scene *scene) {
    // bind this input to inputInstance
    Debug::show("[>] Interaction Attached");
    this->input = new Input(scene->currentWindow->glRef());
}

void InteractionLayer::processInput(Scene *scene) {
    processCameraInput(scene);
}

void InteractionLayer::processCameraInput(Scene *scene) {
    /// todo add mappings for camera keys, for now just use wasd

    float speed = 0.005;
    float sensitivity = 1;

    if (input->isKeyPressed(GLFW_KEY_W)) {
        scene->currentCamera->moveForward(speed);
    };

    if (input->isKeyPressed(GLFW_KEY_S)) {
        scene->currentCamera->moveBackward(speed);
    };

    if (input->isKeyPressed(GLFW_KEY_A)) {
        scene->currentCamera->moveLeft(speed);
    };

    if (input->isKeyPressed(GLFW_KEY_D)) {
        scene->currentCamera->moveRight(speed);
    };

    if (input->isKeyPressed(GLFW_KEY_SPACE)) {
        scene->currentCamera->moveUp(speed);
    };

    if (input->isKeyPressed(GLFW_KEY_X)) {
        scene->currentCamera->moveDown(speed);
    };

    if (Input::isRightMouseDragging()) {
        glm::vec2 delta = Input::getDragDistance();
        scene->currentCamera->rotate(delta.x * sensitivity, -delta.y * sensitivity, true);
    }

    if (selectedModel) {
        if (input->isKeyPressed(GLFW_KEY_I) | input->isKeyPressed(GLFW_KEY_KP_8)) {
            glm::vec3 pos = selectedModel->getPosition();
            pos.y += speed / 2;
            selectedModel->setPosition(pos);
        };
        if (input->isKeyPressed(GLFW_KEY_K) | input->isKeyPressed(GLFW_KEY_KP_2)) {
            glm::vec3 pos = selectedModel->getPosition();
            pos.y -= speed / 2;
            selectedModel->setPosition(pos);
        };
        if (input->isKeyPressed(GLFW_KEY_L) | input->isKeyPressed(GLFW_KEY_KP_ADD)) {
            glm::vec3 pos = selectedModel->getPosition();
            pos.z += speed / 2;
            selectedModel->setPosition(pos);
        };
        if (input->isKeyPressed(GLFW_KEY_O) | input->isKeyPressed(GLFW_KEY_KP_SUBTRACT)) {
            glm::vec3 pos = selectedModel->getPosition();
            pos.z -= speed / 2;
            selectedModel->setPosition(pos);
        };
        if (input->isKeyPressed(GLFW_KEY_PERIOD) | input->isKeyPressed(GLFW_KEY_KP_6)) {
            glm::vec3 pos = selectedModel->getPosition();
            pos.x += speed / 2;
            selectedModel->setPosition(pos);
        };
        if (input->isKeyPressed(GLFW_KEY_COMMA) | input->isKeyPressed(GLFW_KEY_KP_4)) {
            glm::vec3 pos = selectedModel->getPosition();
            pos.x -= speed / 2;
            selectedModel->setPosition(pos);
        };
        if (input->isKeyPressed(GLFW_KEY_R)) {
            Debug::resetIteration();
        };
    }
};