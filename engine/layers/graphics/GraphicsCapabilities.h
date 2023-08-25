#pragma once
#include <iostream>
#include <string>

class GraphicsCapabilities {
    friend class GraphicsAPI;
    friend class API_OpenGL;
    friend class API_DIRECTX;

protected:
    std::string gpuName;
    int maxTextureUnits = 0;
    int maxResolutionX = 0;
    int maxResolutionY = 0;
    int maxAnisotropy = 0;
    int maxRenderTargets = 0;
    int maxUniformBufferBindings = 0;
    // Add more properties here

public:
    GraphicsCapabilities()= default;
};
