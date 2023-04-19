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

    float speed = 10; // travel speed
    float movement = speed / scene->currentFrameRate;


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

    if (selectedModel) {
        if (input->isKeyPressed(GLFW_KEY_I) | input->isKeyPressed(GLFW_KEY_KP_8)) {
            glm::vec3 pos = selectedModel->getPosition();
            pos.y += movement / 2;
            selectedModel->setPosition(pos);
        };
        if (input->isKeyPressed(GLFW_KEY_K) | input->isKeyPressed(GLFW_KEY_KP_2)) {
            glm::vec3 pos = selectedModel->getPosition();
            pos.y -= movement / 2;
            selectedModel->setPosition(pos);
        };
        if (input->isKeyPressed(GLFW_KEY_L) | input->isKeyPressed(GLFW_KEY_KP_ADD)) {
            glm::vec3 pos = selectedModel->getPosition();
            pos.z += movement / 2;
            selectedModel->setPosition(pos);
        };
        if (input->isKeyPressed(GLFW_KEY_O) | input->isKeyPressed(GLFW_KEY_KP_SUBTRACT)) {
            glm::vec3 pos = selectedModel->getPosition();
            pos.z -= movement / 2;
            selectedModel->setPosition(pos);
        };
        if (input->isKeyPressed(GLFW_KEY_PERIOD) | input->isKeyPressed(GLFW_KEY_KP_6)) {
            glm::vec3 pos = selectedModel->getPosition();
            pos.x += movement / 2;
            selectedModel->setPosition(pos);
        };
        if (input->isKeyPressed(GLFW_KEY_COMMA) | input->isKeyPressed(GLFW_KEY_KP_4)) {
            glm::vec3 pos = selectedModel->getPosition();
            pos.x -= movement / 2;
            selectedModel->setPosition(pos);
        };
        if (input->isKeyPressed(GLFW_KEY_R)) {
            Debug::resetIteration();
        };
    }
};