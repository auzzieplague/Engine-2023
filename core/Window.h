#ifndef COMPONENTLAYOUT_WINDOW_H
#define COMPONENTLAYOUT_WINDOW_H

#include "Base.h"
#include "../vendor/includes/glad/glad.h"
#include "../vendor/includes/GLFW/glfw3.h"
#include "../vendor/includes/GLFW/glfw3native.h"


class Window {
public:
    GLFWwindow *glRef{};
    static GLFWwindow *currentWindow;
    bool initialised = false;

    static void (*onWindowUpdate)(GLFWwindow* window, int width, int height);

    Window(uint32_t width, uint32_t height, const std::string& title) {
        this->setupWindow(width, height, title);
    }

    GLFWwindow* setupWindow(uint32_t width, uint32_t height, const std::string& title);
    GLFWwindow* getWindow();
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

};

#endif //COMPONENTLAYOUT_WINDOW_H
