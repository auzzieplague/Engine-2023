#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include "Debug.h"
class Input {
public:
    static bool leftMouseDragging;
    static bool rightMouseDragging;
    static glm::vec2 mousePos;
    static glm::vec2 lastMousePos;
    static Input *instance;

    ///todo sub out glfw window with  window and switch callback assignment based on api
    explicit Input(GLFWwindow* window) : m_window(window) {
        // Initialize key states to "not pressed"
        for (bool & m_key : m_keys) {
            m_key = false;
        }

        // Initialize mouse button states to "not pressed"
        for (bool & m_mouseButton : m_mouseButtons) {
            m_mouseButton = false;
        }

        instance = this;
        setCallbacksOnWindow(window);
    }

    static glm::vec2 getMousePos ();
    static glm::vec2 getLastMousePos ();

    static Input * getInstance(){
        if (Input::instance == nullptr){
            Debug::show("Input is not yet initialised with a window");
        }

        return Input::instance;
    }

    void setCallbacksOnWindow(GLFWwindow* window){
        glfwSetKeyCallback(window, keyCallback);
        glfwSetMouseButtonCallback(window, mouseButtonCallback);
        glfwSetCursorPosCallback(window, mouseMoveCallback);
    }

    [[nodiscard]] bool isKeyPressed(int key) const {
        if (key >= 0 && key < 1024) {
            return m_keys[key];
        }
        return false;
    }

    [[nodiscard]] bool isMouseButtonPressed(int button) const {
        if (button >= 0 && button < 8) {
            return m_mouseButtons[button];
        }
        return false;
    }


    static bool isMouseDragging();
    static bool isLeftMouseDragging();
    static bool isRightMouseDragging();

private:
    GLFWwindow* m_window;
    bool m_keys[1024]{};
    bool m_mouseButtons[8]{};

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) ;
    static void mouseMoveCallback(GLFWwindow *window, double xpos, double ypos);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

};