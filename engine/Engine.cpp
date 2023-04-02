//
// Created by auzzi on 24/03/2023.
//

#include "Engine.h"

#include <ranges>

Engine *Engine::instance;

Engine::Engine(uint32_t width, uint32_t height, const std::string &title, Scene *scene) {
//    window = new Window(width, height, title);
    this->currentScene = scene ? scene : new Scene();
    Engine::instance = this;
}

void Engine::start() {
    this->loopLayers();
}

void Engine::loopLayers() const {
    if (Window::currentWindow) {
        while (!glfwWindowShouldClose(Window::currentWindow)) {
            for (Layer* layer : this->layers) {
                layer->beforeUpdate(this->currentScene);
            }

            for (Layer* layer : this->layers) {
                layer->update(this->currentScene);
            }

            for (Layer* layer : this->layers) {
                layer->afterUpdate(this->currentScene);
            }

            // passes layers and scene to gui modelRenderer (overridden method)
//            Engine::processAppendedGUItems(this->layers, this->currentScene);

            for (Layer* layer : this->layers) {
                layer->beforeRender(this->currentScene);
            }

            for (Layer* layer : this->layers) {
                layer->render(this->currentScene);
            }

            // process input front to back
            for (auto layer : std::ranges::reverse_view(this->layers)) {
                layer->processInput(this->currentScene);
            }

            for (auto layer : std::ranges::reverse_view(this->layers)) {
                layer->afterRender(this->currentScene);
            }

//            glfwPollEvents();
        }
    }

    Engine::stop();
}

void Engine::stop() const {
    delete this->currentScene;
}

void Engine::addComponent(Component *component) {
    currentScene->addComponent(component);
}

void Engine::attachLayer(Layer *layer) {
    layer->onAttach(this->currentScene);
    // todo layer ordering
    this->layers.push_back(layer);
}
