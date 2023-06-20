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

    if (Input::isKeyPressed(GLFW_KEY_R)) {
        Debug::resetIteration();
    };
}

void InteractionLayer::handleCharacterKeys(float movement) {
    if (Input::isKeyPressed(GLFW_KEY_UP) | Input::isKeyPressed(GLFW_KEY_KP_8)) {
        glm::vec3 pos = selectedModel->getWorldPosition();
        pos.y += movement / 2;
        selectedModel->setWorldPosition(pos);

    };
    if (Input::isKeyPressed(GLFW_KEY_DOWN) | Input::isKeyPressed(GLFW_KEY_KP_2)) {
        glm::vec3 pos = selectedModel->getWorldPosition();
        pos.y -= movement / 2;
        selectedModel->setWorldPosition(pos);

    };
    if (Input::isKeyPressed(GLFW_KEY_PAGE_DOWN) | Input::isKeyPressed(GLFW_KEY_KP_ADD)) {
        glm::vec3 pos = selectedModel->getWorldPosition();
        pos.z += movement / 2;
        selectedModel->setWorldPosition(pos);

    };
    if (Input::isKeyPressed(GLFW_KEY_PAGE_UP) | Input::isKeyPressed(GLFW_KEY_KP_SUBTRACT)) {
        glm::vec3 pos = selectedModel->getWorldPosition();
        pos.z -= movement / 2;
        selectedModel->setWorldPosition(pos);
    };
    if (Input::isKeyPressed(GLFW_KEY_RIGHT) | Input::isKeyPressed(GLFW_KEY_KP_6)) {
        glm::vec3 pos = selectedModel->getWorldPosition();
        pos.x += movement / 2;
        selectedModel->setWorldPosition(pos);
    };
    if (Input::isKeyPressed(GLFW_KEY_LEFT) | Input::isKeyPressed(GLFW_KEY_KP_4)) {
        glm::vec3 pos = selectedModel->getWorldPosition();
        pos.x -= movement / 2;
        selectedModel->setWorldPosition(pos);
    };

    if (Input::isKeyPressed(GLFW_KEY_U)) {
        selectedModel->rotateX(0.1);
    }

    if (Input::isKeyPressed(GLFW_KEY_I)) {
        selectedModel->rotateY(0.1);
    }

    if (Input::isKeyPressed(GLFW_KEY_O)) {
        selectedModel->rotateZ(0.1);
    }

    if (Input::isKeyPressed(GLFW_KEY_R)) {
        selectedModel->roll(0.1);
    }

    if (Input::isKeyPressed(GLFW_KEY_P)) {
        selectedModel->pitch(0.1);
    }

    if (Input::isKeyPressed(GLFW_KEY_Y)) {
        selectedModel->yaw(0.1);
    }
}

void InteractionLayer::handleCharacterKeysWithPhysics() {
    float force = .01; // the force to apply to objects

    if (Input::isKeyPressed(GLFW_KEY_I) | Input::isKeyPressed(GLFW_KEY_KP_8)) {
        selectedModel->applyImpulse(glm::vec3{0, 0, -force});
    }
    if (Input::isKeyPressed(GLFW_KEY_K) | Input::isKeyPressed(GLFW_KEY_KP_2)) {

        selectedModel->applyImpulse(glm::vec3{0, 0, +force});
    }
    if (Input::isKeyPressed(GLFW_KEY_L) | Input::isKeyPressed(GLFW_KEY_KP_ADD)) {
        selectedModel->applyImpulse(glm::vec3{0, force+.2, 0});
    }
    if (Input::isKeyPressed(GLFW_KEY_O) | Input::isKeyPressed(GLFW_KEY_KP_SUBTRACT)) {
        selectedModel->applyImpulse(glm::vec3{0, -force, 0});
    }
    if (Input::isKeyPressed(GLFW_KEY_PERIOD) | Input::isKeyPressed(GLFW_KEY_KP_6)) {
        selectedModel->applyImpulse(glm::vec3{force, 0, 0});
    }
    if (Input::isKeyPressed(GLFW_KEY_COMMA) | Input::isKeyPressed(GLFW_KEY_KP_4)) {
        selectedModel->applyImpulse(glm::vec3{-force, 0, 0});
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
    selectedObjectGui(scene);
}

void InteractionLayer::showTransform (std::string text, Transform transform) {
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

void InteractionLayer::displayComponents(Component * component)
{
    //todo add a static queue of object references, right click go
    // Display the component name and create a collapsible section
    if (ImGui::CollapsingHeader(component->getName().c_str()))
    {
        // Check if the right mouse button is clicked on the child component
        showTransform("Local xform", currentScene->selectedComponent->localTransform);
        showTransform("World xform", currentScene->selectedComponent->worldTransform);
        ImGui::Indent(); // Indent to represent nesting
        // Display child components recursively
        for (auto* child : component->childComponents)
        {
            displayComponents(child);

            // Check if the child component is clicked
            if (ImGui::IsItemClicked(0))
            {
                currentScene->selectedComponent = child;
            }
        }

        ImGui::Unindent(); // Remove the indent
    }
}

void InteractionLayer::selectedObjectGui(Scene *scene) {
    ImGui::Begin("Selected Item");
    if (currentScene->selectedComponent->parentComponent && ImGui::Button("..Back"))
    {
        currentScene->selectedComponent =  currentScene->selectedComponent->parentComponent;
    }

    if (scene->selectedComponent) {
        displayComponents(scene->selectedComponent);
    }

    ImGui::End();
}
