//
// Created by auzzi on 24/03/2023.
//

#include "Engine.h"

Engine *Engine::instance;

Engine::Engine(uint32_t width, uint32_t height, const std::string &title, Scene *scene) {
    window = new Window(width, height, title);
    this->currentScene = scene? scene : new Scene();
    Engine::instance = this;
}

void Engine::start() {
    this->loopLayers();
}

void Engine::loopLayers() const {
    if (Window::currentWindow){
        while (!glfwWindowShouldClose(Window::currentWindow)) {
        }
    }

    Engine::stop();
}

void Engine::stop() const {
    delete this->currentScene;
}
