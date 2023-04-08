#pragma once

#include "Base.h"
#include "../vendor/includes/glad/glad.h"
#include "../vendor/includes/GLFW/glfw3.h"
#include "../vendor/includes/GLFW/glfw3native.h"

class GraphicsAPI;

class Window {
public:
    GLFWwindow *glRef{};
    static GLFWwindow *currentWindow;
    bool initialised = false;
    static GraphicsAPI *api;

    static void (*onWindowUpdate)(GLFWwindow *window, int width, int height);

    Window(GraphicsAPI *, uint32_t width, uint32_t height, const std::string &title);

    GLFWwindow *setupWindow(uint32_t width, uint32_t height, const std::string &title);

    GLFWwindow *getWindow();

    static void framebufferSizeCallback(GLFWwindow *window, int width, int height);
};

