#pragma once

#include "Input.h"
#include <string>


Input *Input::instance = nullptr;
bool Input::leftMouseDragging = false;
bool Input::rightMouseDragging = false;
glm::vec2 Input::mousePos;
glm::vec2 Input::lastMousePos;

double Input::lastMouseX = 0.0;
double Input::lastMouseY = 0.0;
double Input::mouseX = 0.0;
double Input::mouseY = 0.0;


void Input::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    Input *input = Input::getInstance();
    if (input) {
        if (key >= 0 && key < 1024) {
            if (action == GLFW_PRESS) {
                input->m_keys[key] = true;
            } else if (action == GLFW_RELEASE) {
                input->m_keys[key] = false;
            }
        } else {
            Debug::show("unable to handle key: " + std::to_string(key));
            Debug::show("- has scancode " + std::to_string(scancode));
            Debug::show("- and modifiers " + std::to_string(mods));
        }
    }
}

void Input::mouseMoveCallback(GLFWwindow *window, double xpos, double ypos) {
    mousePos.x = xpos;
    mousePos.y = ypos;
}

void Input::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {


    Input *input = Input::getInstance();
    if (input) {
        if (button >= 0 && button < 8) {
            if (action == GLFW_PRESS) {
                Debug::show("clicked mouse button: " + std::to_string(button));
                input->m_mouseButtons[button] = true;
            } else if (action == GLFW_RELEASE) {
                input->m_mouseButtons[button] = false;
            }
        }
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        leftMouseDragging = true;
        lastMousePos = mousePos;
    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        leftMouseDragging = false;
    }

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        rightMouseDragging = true;
        lastMousePos = mousePos;
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        rightMouseDragging = false;
    }
}

bool Input::isMouseDragging() {
    return leftMouseDragging | rightMouseDragging;
}

bool Input::isLeftMouseDragging() {
    return leftMouseDragging;
}


bool Input::isRightMouseDragging() {
    return rightMouseDragging;
}

glm::vec2 Input::getLastMousePos() {
    return lastMousePos;
}

glm::vec2 Input::getMousePos() {
    return mousePos;
}
