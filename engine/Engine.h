#pragma once

#include "Object.h"
#include "Scene.h"
#include "layers/GraphicsLayer.h"
#include "../engine/layers/WindowLayer.h"
#include "../engine/layers/graphics/api/API_OpenGL.h"
#include "../engine/layers/InteractionLayer.h"

class Engine : public Object {
private:
    Scene *currentScene{};
    Scene *nextScene{}; // for preloading
    std::vector<Layer *> layers;
    GraphicsAPI *graphicsAPI;
public:
    void setGraphicsApi(GraphicsAPI *api);

private:
    Window *window{};

    static Engine *instance;

public:
    explicit Engine(uint32_t width = 1600, uint32_t height = 800, const std::string &title = "Onion",
                    Scene *scene = nullptr);

    static Engine *getInstance();

    void attachLayer(Layer *layer); // initialises layer

    void addComponent(Component *component); // passthrough to scene

    void start();               // kick-start engine
    void loopLayers() const;    // main loop
    void stop() const;          // cleanup
};
