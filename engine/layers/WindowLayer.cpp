#pragma once

#include "WindowLayer.h"
//
//WindowLayer::WindowLayer(GraphicsAPI *api) {
//    this->api = api;
//}

void WindowLayer::onAttach(Scene * scene){
    Debug::show("Spawning Window");
    scene->currentWindow = new Window(api,1280, 720, "Window Layer");
}

void WindowLayer::onDetach(Scene *) {
    Debug::show("Killing Window");
}

void WindowLayer::processInput(Scene *scene) {
    //todo move to api
    glfwPollEvents();

    if (glfwGetKey(scene->currentWindow->glRef, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(scene->currentWindow->glRef, true);
    }
}

void WindowLayer::afterRender(Scene *scene) {
    glfwSwapBuffers(scene->currentWindow->glRef);
}