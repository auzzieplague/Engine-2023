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

    [[maybe_unused]] GLFWwindow *m_window{};
    bool m_keys[1024]{};
    bool m_mouseButtons[8]{};

    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

    static void mouseMoveCallback(GLFWwindow *window, double xPos, double yPos);

    static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

public:
    [[maybe_unused]] [[nodiscard]] static bool isMouseDragging();

    [[maybe_unused]] [[nodiscard]]static bool isLeftMouseDragging();

    [[nodiscard]] static bool isRightMouseDragging();

    [[maybe_unused]] [[nodiscard]] const bool *getMMouseButtons() const;

    [[maybe_unused]] [[nodiscard]] static glm::vec2 getMousePos();

    [[maybe_unused]] [[nodiscard]] static glm::vec2 getLastMousePos();

    [[nodiscard]] static glm::vec2 getDragDistance();

    [[nodiscard]] bool isKeyPressed(int key) const;

    [[maybe_unused]] [[nodiscard]] bool isMouseButtonPressed(int button) const;

    /// todo sub out glfw window with  window and switch callback assignment based on m_api
    explicit Input(GLFWwindow *window);

    [[nodiscard]] static Input *getInstance();

    void setCallbacksOnWindow(GLFWwindow *window);


};