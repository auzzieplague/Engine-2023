#pragma once

#include "Input.h"
bool Input::mouseDragging = false;
double Input::lastMouseX = 0.0;
double Input::lastMouseY = 0.0;

void Input::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));
    if (input) {
        if (key >= 0 && key < 1024) {
            if (action == GLFW_PRESS) {
                input->m_keys[key] = true;
            } else if (action == GLFW_RELEASE) {
                input->m_keys[key] = false;
            }
        }
    }
}

void Input::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)  {

    Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));
    if (input) {
        if (button >= 0 && button < 8) {
            if (action == GLFW_PRESS) {
                input->m_mouseButtons[button] = true;
            } else if (action == GLFW_RELEASE) {
                input->m_mouseButtons[button] = false;
            }
        }
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        mouseDragging = true;
        glfwGetCursorPos(window, &lastMouseX, &lastMouseY);
    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        mouseDragging = false;
    }
}