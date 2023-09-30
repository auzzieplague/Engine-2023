#pragma once

#include "GraphicsAPI.h"

/**
 * requires glfw3.lib installed
 */
class API_OpenGL : public GraphicsAPI {

    void queryCapabilities() override;
//
    static bool isExtensionSupported(const char* extensionName);
};

