#include <Window.h>
#include <GraphicsAPI.h>

GLFWwindow *Window::m_currentWindow = nullptr;
GraphicsAPI *Window::m_api;

GLFWwindow *Window::setupWindow(uint32_t width, uint32_t height, const std::string &title) {

    /// setup windowContext struct to allow abstraction of API - then put this into API_openGL
    // init libs and window
    if (!glfwInit()) return nullptr;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_SAMPLES, 4); // multisampling for antialiasing 

    GLFWwindow *window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    this->m_glRef = window;
    Window::m_currentWindow = window;
    this->m_ready = true;

    this->width= width;
    this->height = height;
    glfwSetFramebufferSizeCallback(m_glRef, Window::framebufferSizeCallback);

    return window;
}

[[maybe_unused]] GLFWwindow *Window::getWindow() {
    if (!this->m_ready) {
        setupWindow(1200, 720, "default window");
        if (!this->m_ready) {
            throw std::runtime_error("the window could not be mReady");
        }
    }
    return this->m_glRef;
}

void Window::framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    // update engine stuff - window details, projection matrix etc
    if (onWindowUpdate){
        onWindowUpdate(window,width,height);
    }

    // update API stuff e.g. glViewPort
    m_api->resizeViewport(width, height, window);
}

Window::Window(GraphicsAPI *graphicsAPI, uint32_t width, uint32_t height, const std::string &title) {
    m_api = graphicsAPI;
    this->setupWindow(width, height, title);
}

GLFWwindow *Window::glRef() const {
    return m_glRef;
}

GLFWwindow *Window::getCurrentWindow() {
    return m_currentWindow;
}

[[maybe_unused]] bool Window::isReady() const {
    return m_ready;
}

GraphicsAPI *Window::api() {
    return m_api;
}

int Window::getWidth() const {
    return width;
}

int Window::getHeight() const {
    return height;
}
