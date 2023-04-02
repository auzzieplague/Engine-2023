#pragma once

#include "Object.h"
#include "Scene.h"
#include "layers/GraphicsLayer.h"
#include "../core/Core.h"

class Engine : public Object {
    Scene *currentScene{};
    Scene *nextScene{}; // for preloading
    std::vector<Layer *> layers;

    Window *window{};

    static Engine *instance;

public:
    explicit Engine(uint32_t width = 1600, uint32_t height = 800, const std::string &title = "Onion",
                    Scene *scene = nullptr);

    static Engine *getInstance() {
        if (!instance) {
            instance = new Engine();
        }
        return instance;
    }

    void attachLayer(Layer* layer); // initialises layer

    void addComponent(Component *component);

    void start();               // kick-start engine
    void loopLayers() const;    // main loop
    void stop() const;          // cleanup

};
