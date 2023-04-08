#pragma once

#include "WindowLayer.h"

WindowLayer::WindowLayer(GraphicsAPI *api) {
    this->api = api;
}

void WindowLayer::onAttach(Scene *){
    Debug::show("Spawning Window");
    this->window = new Window(api,1280, 720, "Window Layer");
}

void WindowLayer::onDetach(Scene *) {
    Debug::show("Killing Window");
}

void WindowLayer::processInput(Scene *scene) {
    //todo move to api
    glfwPollEvents();

    if (glfwGetKey(window->glRef, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window->glRef, true);
    }
}

void WindowLayer::afterRender(Scene *scene) {
    glfwSwapBuffers(window->glRef);
}