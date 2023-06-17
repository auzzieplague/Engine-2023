#pragma once

#include "Input.h"
#include <string>


Input *Input::m_instance = nullptr;
bool Input::m_leftMouseDragging = false;
bool Input::m_rightMouseDragging = false;
glm::vec2 Input::m_mousePos;
glm::vec2 Input::m_lastMousePos;
bool Input::m_keys[1024]{};
bool Input::m_mouseButtons[8]{};

Input::Input(GLFWwindow *window) {
    // Initialize key states to "not pressed"
    for (bool &m_key: m_keys) {
        m_key = false;
    }

    // Initialize mouse button states to "not pressed"
    for (bool &m_mouseButton: m_mouseButtons) {
        m_mouseButton = false;
    }

    m_instance = this;
    setCallbacksOnWindow(window);
}

Input *Input::getInstance() {
    if (Input::m_instance == nullptr) {
        Debug::show("Input is not yet m_ready with a window");
    }

    return Input::m_instance;
}


[[maybe_unused]] bool Input::isMouseDragging() {
    return m_leftMouseDragging | m_rightMouseDragging;
}

[[maybe_unused]] bool Input::isLeftMouseDragging() {
    return m_leftMouseDragging;
}

bool Input::isRightMouseDragging() {
    return m_rightMouseDragging;
}

[[maybe_unused]] glm::vec2 Input::getLastMousePos() {
    return m_lastMousePos;
}

[[maybe_unused]] glm::vec2 Input::getMousePos() {
    return m_mousePos;
}

[[maybe_unused]] const bool *Input::getMMouseButtons() const {
    return m_mouseButtons;
}

glm::vec2 Input::getDragDistance() {
    glm::vec2 delta = m_mousePos - m_lastMousePos;
    m_lastMousePos = m_mousePos;
    return delta;
}

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

void Input::mouseMoveCallback(GLFWwindow *window, double xPos, double yPos) {
    m_mousePos.x = static_cast<float>(xPos);
    m_mousePos.y = static_cast<float>(yPos);
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
        m_leftMouseDragging = true;
        m_lastMousePos = m_mousePos;
    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        m_leftMouseDragging = false;
    }

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        m_rightMouseDragging = true;
        m_lastMousePos = m_mousePos;
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        m_rightMouseDragging = false;
    }
}

void Input::setCallbacksOnWindow(GLFWwindow *window) {
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, mouseMoveCallback);
}

bool Input::isKeyPressed(int key)  {
    if (key >= 0 && key < 1024) {
        return m_keys[key];
    }
    return false;
}

[[maybe_unused]] bool Input::isMouseButtonPressed(int button) {
    if (button >= 0 && button < 8) {
        return m_mouseButtons[button];
    }
    return false;
}

