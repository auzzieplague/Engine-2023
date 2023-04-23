
#include "Engine.h"

Engine *Engine::instance;

Engine::Engine(uint32_t width, uint32_t height, const std::string &title, Scene *scene) {
//    window = new Window(width, height, title);
    this->currentScene = scene ? scene : new Scene();
    Engine::instance = this;
}

void Engine::start() {
    this->loopLayers();
}

void Engine::loopLayers()  {
    initFrameTimer();

    if (Window::getCurrentWindow()) {
        while (!glfwWindowShouldClose(Window::getCurrentWindow())) {

            for (Layer *layer: this->layers) {
                layer->beforeUpdate(this->currentScene);
            }

            for (Layer *layer: this->layers) {
                layer->update(this->currentScene);
            }

            for (Layer *layer: this->layers) {
                layer->afterUpdate(this->currentScene);
            }

            // passes layers and scene to gui modelRenderer (overridden method)
            // Engine::processAppendedGUItems(this->layers, this->currentScene);

            for (Layer *layer: this->layers) {
                layer->beforeRender(this->currentScene);
            }

            for (Layer *layer: this->layers) {
                layer->render(this->currentScene);
            }

            for (auto it = std::rbegin(this->layers); it != std::rend(this->layers); ++it) {
                (*it)->processInput(this->currentScene);
            }

            for (auto it = std::rbegin(this->layers); it != std::rend(this->layers); ++it) {
                (*it)->afterRender(this->currentScene);
            }

            // pass down framerate value to scene for use by layers
            this->currentScene->currentFrameRate = this->getCurrentFramerate();
//            glfwPollEvents();
        }
    }

    Engine::stop();
}

void Engine::stop() {
    delete this->currentScene;
}

void Engine::addComponent(Component *component) {
    currentScene->addComponent(component);
}

void Engine::attachLayer(Layer *layer) {
    //assign graphics m_api into layer
    layer->setApi(this->graphicsAPI);

    //run attach hook
    layer->onAttach(this->currentScene);


    // todo layer ordering
    this->layers.push_back(layer);
}

Engine *Engine::getInstance() {
    {
        if (!instance) {
            instance = new Engine();
            instance->graphicsAPI = new API_OpenGL();
        }
        return instance;
    }
}

void Engine::setGraphicsApi(GraphicsAPI *api) {
    Engine::graphicsAPI = api;
}

void Engine::initFrameTimer() {
    lastTime = std::chrono::high_resolution_clock::now();
}

float Engine::getCurrentFramerate() {

    // Get the current timestamp
    auto now = std::chrono::high_resolution_clock::now();

    // Calculate the elapsed time since the previous frame
    std::chrono::duration<double> elapsed = now - lastTime;

    // Calculate the current framerate by dividing 1 by the elapsed time
    float framerate = 1.0f / elapsed.count();

    // Update lastTime to the current timestamp for the next frame
    lastTime = now;

    return framerate;
};