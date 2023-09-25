#pragma once
#include "../core/Performance.h"
#include "Object.h"
#include "Scene.h"
#include <GraphicsLayer.h>
#include <WindowLayer.h>
#include <API_OpenGL.h>
#include <chrono>

class Engine : public Object {
private:
    Scene *nextScene{}; // for preloading
    std::vector<Layer *> layers;
    GraphicsAPI *graphicsAPI = nullptr;
    bool initialised = false;
    bool hasGUILayer = false;

public:
    void setGraphicsApi(GraphicsAPI *api);

    Scene *currentScene{};
    Window *window{};
    static Engine *instance;

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
    void start();               // kick-start engine
    void loopLayers();          // main loop
    void stop();          // cleanup
    void initLayers();

    void static onWindowUpdate(GLFWwindow *window, int width, int height);

    void processGUILayers();
};
