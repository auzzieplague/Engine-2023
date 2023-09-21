#pragma once
#include <iostream>
#include <string>

class GraphicsCapabilities {
    friend class GraphicsAPI;
    friend class API_OpenGL;
    friend class API_DIRECTX;

public:
    std::string gpuName;
    int maxTextureUnits = 0;
    int maxResolutionX = 0;
    int maxResolutionY = 0;
    int maxAnisotropy = 0;
    int maxRenderTargets = 0;
    int maxUniformBufferBindings = 0;
    int maxMultisampleSamples = 0; // Example property for maximum multisample antialiasing samples
    int maxConstantBufferSize = 0; // Example property for maximum constant buffer size
    int maxVertexBufferSize = 0; // Example property for maximum vertex buffer size
    int maxIndexBufferSize = 0; // Example property for maximum index buffer size
    int maxPrimitiveTopology = 0; // Example property for supported primitive topologies

public:
    GraphicsCapabilities()= default;
};
