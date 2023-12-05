
#include "GraphicsBehaviour.h"
#include <string>
#include <iostream>


void GraphicsBehaviour::displayCapabilities() {
    Debug::show("GPU Model: " + gpuInfo->model);
    Debug::show("VRAM Size (MB): " + std::to_string(gpuInfo->VRAMSize));
    Debug::show("Driver Version: " +  gpuInfo->driverVersion);
    Debug::show("Shader ModelVersion Support: " +  gpuInfo->shaderModelVersionSupport);
    Debug::show("ShaderLanguageSupport: " +  gpuInfo->shaderLanguageSupport);
    Debug::show("Texture Compression Formats: " +  gpuInfo->textureCompressionFormats);
    Debug::show("OpenGL Version Support: " +  gpuInfo->openGLVersionSupport);
    Debug::show("Max Texture Size: " + std::to_string( gpuInfo->maxTextureSize));
    Debug::show("Max Render Target Size: " + std::to_string( gpuInfo->maxRenderSize));
    Debug::show("Max Anisotropic Filtering: " + std::to_string( gpuInfo->maxAnisotropicFiltering));
    Debug::show("Max MSAA Level: " + std::to_string( gpuInfo->maxMSAA));
    Debug::show("Max Texture Units: " + std::to_string( gpuInfo->maxTextureUnits));
    Debug::show("Max Vertex Attributes: " + std::to_string( gpuInfo->maxVertexAttributes));
    Debug::show("Max Uniform Buffer Bindings: " + std::to_string( gpuInfo->maxUniformBindings));
    Debug::show("Max Texture Image Units: " + std::to_string( gpuInfo->maxTextureImageUnits));
    Debug::show("Max Geometry Output Vertices: " + std::to_string( gpuInfo->maxGeometryOutputVertices));
    Debug::show("Max Geometry Output Components: " + std::to_string( gpuInfo->maxGeometryOutputComponents));
    Debug::show(gpuInfo->tessellationSupport ? "Tessellation Support: Yes" : "Tessellation Support: No");
    Debug::show(gpuInfo->computeShaderSupport ? "Compute Shader Support: Yes" : "Compute Shader Support: No");
    Debug::show(gpuInfo->rayTracingSupport ? "Ray Tracing Support: Yes" : "Ray Tracing Support: No");

    // Display other GPUInfo details as needed
}

MeshData *GraphicsBehaviour::getSampleMeshData() {

    float vertices[] = {
            -0.5f, -0.5f, 0.0f, // Bottom-left corner
            0.5f, -0.5f, 0.0f, // Bottom-right corner
            0.5f, 0.5f, 0.0f, // Top-right corner
            -0.5f, 0.5f, 0.0f  // Top-left corner
    };

//    float vertices[] = {
//            0.0f, 0.0f, 0.0f, // Bottom-left corner
//            0.9f, 0.0f, 0.0f, // Bottom-right corner
//            0.9f, 0.9f, 0.0f, // Top-right corner
//            0.0f, 0.9f, 0.0f  // Top-left corner
//    };

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

//             Positions
    float vertices[] = {
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
    meshData->setVertices(vertices, TINKER_ARRAY_SIZE(vertices));
    meshData->setIndices(indices, TINKER_ARRAY_SIZE(indices));
    meshData->setUVs(uvs, TINKER_ARRAY_SIZE(uvs));

    return meshData;
}

