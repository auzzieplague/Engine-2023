#pragma once
#define GLFW_INCLUDE_VULKAN
#include "GraphicsAPI.h"

class API_Vulkan: public GraphicsAPI {
    bool initialise() override;
//    void queryCapabilities() override;
};

