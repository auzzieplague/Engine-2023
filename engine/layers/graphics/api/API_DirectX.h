#pragma once

#include "GraphicsAPI.h"

class API_DirectX : public GraphicsAPI {
    void framebufferSizeCallback(GLFWwindow *window, int width, int height) override;
};


