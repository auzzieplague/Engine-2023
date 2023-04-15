#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include "Debug.h"
class Input {
private:
    static bool m_leftMouseDragging;
    static bool m_rightMouseDragging;
    static glm::vec2 m_mousePos;
    static glm::vec2 m_lastMousePos;
    static Input *m_instance;

    GLFWwindow* m_window;
    bool m_keys[1024]{};
    bool m_mouseButtons[8]{};

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) ;
    static void mouseMoveCallback(GLFWwindow *window, double xpos, double ypos);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

public:
    [[nodiscard]] static bool isMouseDragging();
    [[nodiscard]]static bool isLeftMouseDragging();
    [[nodiscard]] static bool isRightMouseDragging();
    [[nodiscard]] const bool *getMMouseButtons() const;
    [[nodiscard]] static glm::vec2 getMousePos ();
    [[nodiscard]] static glm::vec2 getLastMousePos ();
    [[nodiscard]] static glm::vec2 getDragDistance();
    [[nodiscard]] bool isKeyPressed(int key) const ;
    [[nodiscard]] bool isMouseButtonPressed(int button) const ;

    ///todo sub out glfw window with  window and switch callback assignment based on api
    explicit Input(GLFWwindow* window);
    [[nodiscard]] static Input * getInstance();

    void setCallbacksOnWindow(GLFWwindow* window);







};