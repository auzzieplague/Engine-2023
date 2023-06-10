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
        if (selectedModel->mPhysicsBody) {
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
    if (input->isKeyPressed(GLFW_KEY_I) | input->isKeyPressed(GLFW_KEY_KP_8)) {
        glm::vec3 pos = selectedModel->getWorldPosition();
        pos.y += movement / 2;
        selectedModel->setWorldPosition(pos);

    };
    if (input->isKeyPressed(GLFW_KEY_K) | input->isKeyPressed(GLFW_KEY_KP_2)) {
        glm::vec3 pos = selectedModel->getWorldPosition();
        pos.y -= movement / 2;
        selectedModel->setWorldPosition(pos);

    };
    if (input->isKeyPressed(GLFW_KEY_L) | input->isKeyPressed(GLFW_KEY_KP_ADD)) {
        glm::vec3 pos = selectedModel->getWorldPosition();
        pos.z += movement / 2;
        selectedModel->setWorldPosition(pos);

    };
    if (input->isKeyPressed(GLFW_KEY_O) | input->isKeyPressed(GLFW_KEY_KP_SUBTRACT)) {
        glm::vec3 pos = selectedModel->getWorldPosition();
        pos.z -= movement / 2;
        selectedModel->setWorldPosition(pos);
    };
    if (input->isKeyPressed(GLFW_KEY_PERIOD) | input->isKeyPressed(GLFW_KEY_KP_6)) {
        glm::vec3 pos = selectedModel->getWorldPosition();
        pos.x += movement / 2;
        selectedModel->setWorldPosition(pos);
    };
    if (input->isKeyPressed(GLFW_KEY_COMMA) | input->isKeyPressed(GLFW_KEY_KP_4)) {
        glm::vec3 pos = selectedModel->getWorldPosition();
        pos.x -= movement / 2;
        selectedModel->setWorldPosition(pos);
    };

    if (input->isKeyPressed(GLFW_KEY_T)) {
//        selectedModel->rotateAround(selectedModel->getLocalPosition(), glm::vec3(0.1, 0, 0));
        selectedModel->rotateX(0.1);
    }

    if (input->isKeyPressed(GLFW_KEY_Y)) {
//        selectedModel->rotateAround(selectedModel->getLocalPosition(), glm::vec3(0, 0.1, 0));
//        selectedModel->rotateY(0.1);
    }

    if (input->isKeyPressed(GLFW_KEY_U)) {
//        selectedModel->rotateAround(selectedModel->getLocalPosition(), glm::vec3(0, 0, 0.1));
//        selectedModel->rotateZ(0.1);
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