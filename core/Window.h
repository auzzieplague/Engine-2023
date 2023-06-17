#pragma once

#include "Base.h"
#include "../vendor/includes/glad/glad.h"
#include "../vendor/includes/GLFW/glfw3.h"
#include "../vendor/includes/GLFW/glfw3native.h"

class GraphicsAPI;

class Window {
private:
    GLFWwindow *m_glRef{};
    static GLFWwindow *m_currentWindow;
    bool m_ready = false;
    static GraphicsAPI *m_api;
    int width;
public:
    int getWidth() const;

    int getHeight() const;

private:
    int height;
public:
    [[nodiscard]] GLFWwindow *glRef() const;

    [[nodiscard]] static GLFWwindow *getCurrentWindow();

    [[maybe_unused]] [[nodiscard]] bool isReady() const;

    [[nodiscard]] static GraphicsAPI *api();

    [[maybe_unused]] static void (*onWindowUpdate)(GLFWwindow *window, int width, int height);

    Window(GraphicsAPI *, uint32_t width, uint32_t height, const std::string &title);

    GLFWwindow *setupWindow(uint32_t width, uint32_t height, const std::string &title);

    [[maybe_unused]] GLFWwindow *getWindow();

    static void framebufferSizeCallback(GLFWwindow *window, int width, int height);
};

