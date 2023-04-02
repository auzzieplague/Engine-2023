#include "Window.h"

GLFWwindow *Window::currentWindow = nullptr;

GLFWwindow *Window::setupWindow(uint32_t width, uint32_t height, const std::string &title) {
    // init libs and window
    if (!glfwInit()) return nullptr;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    this->glRef = window;
    Window::currentWindow = window;
    this->initialised = true;

    glfwSetFramebufferSizeCallback(glRef, Window::framebuffer_size_callback);

    return window;
}

GLFWwindow *Window::getWindow() {
    if (!this->initialised) {
        setupWindow(1200, 720, "default window");
        if (!this->initialised) {
            throw std::runtime_error("the window could not be initialised");
        }
    }
    return this->glRef;
}

void Window::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);

    // if virtual function has been assigned, give it a call
//    if (onWindowUpdate) {
//        onWindowUpdate(window, width, height);
//    }
}
