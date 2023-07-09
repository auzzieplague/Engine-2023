#pragma once

#include "Object.h"
#include "Scene.h"
#include "layers/GraphicsLayer.h"
#include "../engine/layers/WindowLayer.h"
#include "../engine/layers/graphics/api/API_OpenGL.h"
#include "../engine/layers/InteractionLayer.h"
#include <chrono>

class Engine : public Object {
private:
    Scene *nextScene{}; // for preloading
    std::vector<Layer *> layers;
    GraphicsAPI *graphicsAPI = nullptr;
    bool initialised = false;
public:
    void setGraphicsApi(GraphicsAPI *api);

    Scene *currentScene{};
private:
    Window *window{};

    static Engine *instance;

public:
    explicit Engine(uint32_t width = 1600, uint32_t height = 800, const std::string &title = "Onion",
                    Scene *scene = nullptr);

    static Engine *getInstance();

    // Define a variable to store the previous frame's timestamp
    std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;

// Call this function at the start of the render loop to initialize lastTime
    void initFrameTimer();

// Call this function at the end of the render loop to calculate the current framerate
    float getCurrentFramerate();

    void attachLayer(Layer *layer); // initialises layer

    void addComponent(Component *component); // passthrough to scene

    void start();               // kick-start engine
    void loopLayers();          // main loop
    void stop();          // cleanup
    void initLayers();

};
