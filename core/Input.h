#include <GLFW/glfw3.h>

class Input {
public:
    static bool mouseDragging;
    static double lastMouseX;
    static double lastMouseY;

    ///todo sub out glfw window with  window and switch callback assignment based on api
    Input(GLFWwindow* window) : m_window(window) {
        // Initialize key states to "not pressed"
        for (bool & m_key : m_keys) {
            m_key = false;
        }

        // Initialize mouse button states to "not pressed"
        for (bool & m_mouseButton : m_mouseButtons) {
            m_mouseButton = false;
        }

        // Set up GLFW event callbacks
        glfwSetKeyCallback(m_window, keyCallback);
        glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
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

private:
    GLFWwindow* m_window;
    bool m_keys[1024]{};
    bool m_mouseButtons[8]{};

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) ;

    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
};