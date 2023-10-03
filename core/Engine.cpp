
#include "Engine.h"

Engine *Engine::instance;

void (*Window::onWindowUpdate)(GLFWwindow *window, int width, int height);

Engine::Engine(uint32_t width, uint32_t height, const std::string &title, Scene *scene) {
//    window = new Window(width, height, title);
    this->currentScene = scene ? scene : new Scene();
    Engine::instance = this;
}

void Engine::start() {
//    AssetManager::initialise();
    Window::onWindowUpdate = &Engine::onWindowUpdate;
    this->initLayers();
    this->loopLayers();
}

void Engine::initLayers() {
    for (Layer *layer: this->layers) {
        layer->currentScene = this->currentScene;
        layer->init(currentScene);
    }
}

void Engine::processGUILayers() {
    if (!this->hasGUILayer) {
        return;
    }

    for (auto *layer: this->layers) {
        layer->appendToGui(this->currentScene);
    }
}

void Engine::loopLayers() {
    initFrameTimer();
    PerformanceMeasurer &perf = PerformanceMeasurer::getInstance();

    if (Window::getCurrentWindow()) {
        while (!glfwWindowShouldClose(Window::getCurrentWindow())) {
            currentScene->currentFrame++;

            for (Layer *layer: this->layers) {
                perf.start("before_update_" + layer->getName());
                layer->beforeUpdate(this->currentScene);
                perf.stop("before_update_" + layer->getName());
            }

            for (Layer *layer: this->layers) {
                perf.start("update_" + layer->getName());
                layer->update(this->currentScene);
                perf.stop("update_" + layer->getName());
            }

            for (Layer *layer: this->layers) {
                perf.start("after_update_" + layer->getName());
                layer->afterUpdate(this->currentScene);
                perf.stop("after_update_" + layer->getName());
            }

            for (Layer *layer: this->layers) {
                perf.start("before_render" + layer->getName());
                layer->beforeRender(this->currentScene);
                perf.stop("before_render" + layer->getName());
            }

            this->processGUILayers();

            for (Layer *layer: this->layers) {
                perf.start("render_" + layer->getName());
                layer->render(this->currentScene);
                perf.stop("render_" + layer->getName());
            }

            perf.start("combined inputs");
            for (auto it = std::rbegin(this->layers); it != std::rend(this->layers); ++it) {
                (*it)->processInput(this->currentScene);
            }
            perf.stop("combined inputs");

            for (auto it = std::rbegin(this->layers); it != std::rend(this->layers); ++it) {
                perf.start("after render_" + (*it)->getName());
                (*it)->afterRender(this->currentScene);
                perf.stop("after render_" + (*it)->getName());
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
    this->graphicsAPI->shutdown();
}

void Engine::attachLayer(Layer *layer) {
    // assign graphics m_api into layer
    layer->setApi(this->graphicsAPI);
    layer->currentScene = this->currentScene;
    layer->onAttach(this->currentScene);
    if (layer->getType() == ObjectType::OT_Layer_GUI) {
        this->hasGUILayer = true;
    }
    // todo layer ordering
    this->layers.push_back(layer);
}

Engine *Engine::getInstance() {
    {
        if (!instance) {
            instance = new Engine();
//            instance->graphicsAPI = new API_OpenGL();
        }
        return instance;
    }
}

void Engine::setGraphicsApi(GraphicsBehaviour *behaviour) {
    auto *api = new GraphicsAPI( behaviour);
    Engine::graphicsAPI = api;
    Material::setGraphicsAPI(api);
    VertexBuffer::setGraphicsAPI(api);
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

void Engine::onWindowUpdate(GLFWwindow *window, int width, int height) {
    // get instance of engine
    Scene *scene = Engine::getInstance()->currentScene;
    scene->currentWindow->width = width;
    scene->currentWindow->height = height;
    scene->currentCamera->updateProjectionMatrix();
}