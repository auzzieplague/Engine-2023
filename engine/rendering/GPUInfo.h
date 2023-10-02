#pragma once

#include <string>

class GPUInfo {
public:
    GPUInfo()= default;

    ~GPUInfo()= default;

    std::string model{};
    std::string driverVersion{};
    std::string openGLVersionSupport{};
    std::string directXVersionSupport{};
    std::string vulkanVersionSupport{};
    std::string shaderModelVersionSupport{};
    std::string shaderLanguageSupport{};
    std::string textureCompressionFormats{};
    int VRAMSize = -1;
    int maxTextureSize = -1;
    int maxRenderSize = -1;
    int maxAnisotropicFiltering = -1;
    int maxMSAA = -1;
    int maxTextureUnits =-1;
    int maxVertexAttributes =-1;
    int maxUniformBindings =-1;
    int maxTextureImageUnits =-1;
    int maxGeometryOutputVertices =-1;
    int maxGeometryOutputComponents =-1;

    bool tessellationSupport = false;
    bool computeShaderSupport = false;
    bool rayTracingSupport = false;

//    float getCurrentTemperature();

};
