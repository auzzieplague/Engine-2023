
#include "GraphicsBehaviour.h"
#include <string>
#include <iostream>
#include "graphics/buffers/BufferObject.h"


void GraphicsBehaviour::displayCapabilities(...) {
    std::cout << "GPU Model: " << gpuInfo->model << std::endl;
    std::cout << "VRAM Size (MB): " << gpuInfo->VRAMSize << std::endl;
    std::cout << "Driver Version: " << gpuInfo->driverVersion << std::endl;
    std::cout << "Shader ModelVersion Support: " << gpuInfo->shaderModelVersionSupport << std::endl;
    std::cout << "ShaderLanguageSupport: " << gpuInfo->shaderLanguageSupport << std::endl;
    std::cout << "Texture Compression Formats: " << gpuInfo->textureCompressionFormats << std::endl;
    std::cout << "OpenGL Version Support: " << gpuInfo->openGLVersionSupport << std::endl;
    std::cout << "Max Texture Size: " << gpuInfo->maxTextureSize << std::endl;
    std::cout << "Max Render Target Size: " << gpuInfo->maxRenderSize << std::endl;
    std::cout << "Max Anisotropic Filtering: " << gpuInfo->maxAnisotropicFiltering << std::endl;
    std::cout << "Max MSAA Level: " << gpuInfo->maxMSAA << std::endl;
    std::cout << "Max Texture Units: " << gpuInfo->maxTextureUnits << std::endl;
    std::cout << "Max Vertex Attributes: " << gpuInfo->maxVertexAttributes << std::endl;
    std::cout << "Max Uniform Buffer Bindings: " << gpuInfo->maxUniformBindings << std::endl;
    std::cout << "Max Texture Image Units: " << gpuInfo->maxTextureImageUnits << std::endl;
    std::cout << "Max Geometry Output Vertices: " << gpuInfo->maxGeometryOutputVertices << std::endl;
    std::cout << "Max Geometry Output Components: " << gpuInfo->maxGeometryOutputComponents << std::endl;
    std::cout << "Tessellation Support: " << (gpuInfo->tessellationSupport ? "Yes" : "No") << std::endl;
    std::cout << "Compute Shader Support: " << (gpuInfo->computeShaderSupport ? "Yes" : "No") << std::endl;
    std::cout << "Ray Tracing Support: " << (gpuInfo->rayTracingSupport ? "Yes" : "No") << std::endl;

    // Display other GPUInfo details as needed
}

unsigned int GraphicsBehaviour::getFlagCode(const char *string) {
    return 0;
}

MeshData *GraphicsBehaviour::getSampleMeshData() {

    float vertices[] = {
            -0.5f, -0.5f, 0.0f, // Bottom-left corner
            0.5f, -0.5f, 0.0f, // Bottom-right corner
            0.5f, 0.5f, 0.0f, // Top-right corner
            -0.5f, 0.5f, 0.0f  // Top-left corner
    };

    unsigned int indices[] = {
            0, 1, 2, // First triangle
            2, 3, 0  // Second triangle
    };

    auto meshData = new MeshData();
    meshData->setVertices(vertices, TINKER_ARRAY_SIZE(vertices));
    meshData->setIndices(indices, TINKER_ARRAY_SIZE (indices));

    return meshData;
}

MeshData *GraphicsBehaviour::getFullScreenQuadMeshData() {
    // Vertices of a full-screen quad in NDC
    float vertices[] = {
            // Positions
            -1.0f,  1.0f, 0.0f, // Top-left corner
            -1.0f, -1.0f, 0.0f, // Bottom-left corner
            1.0f, -1.0f, 0.0f, // Bottom-right corner
            1.0f,  1.0f, 0.0f  // Top-right corner
    };

    // UV texture coordinates
    float uvs[] = {
            // UVs
            0.0f, 1.0f, // Top-left corner
            0.0f, 0.0f, // Bottom-left corner
            1.0f, 0.0f, // Bottom-right corner
            1.0f, 1.0f  // Top-right corner
    };

    // Indices for two triangles that make up the quad
    unsigned int indices[] = {
            0, 1, 2, // First triangle
            0, 2, 3  // Second triangle
    };

    auto meshData = new MeshData();
    meshData->setVertices(vertices, sizeof(vertices));
    meshData->setIndices(indices, sizeof(indices));
    meshData->setUVs(uvs, sizeof(uvs));

    return meshData;
};