#pragma once

#include "GraphicsAPI.h"

class API_OpenGL : public GraphicsAPI {
public:

    int transformBufferSize = 1000;
    unsigned int transformBuffer = 0;
    unsigned int transformBufferBindingPoint = 0;

    bool initialise() override;
    void shutdown() override;
    VertexBuffer createVertexBuffer(...) override;
    IndexBuffer createIndexBuffer(...) override;
    Texture loadTexture(...) override;
    Mesh loadMesh(...) override;
    Shader createShader(...) override;
    void setShader(Shader shader) override;
    void setUniform(...) override;
    void bindTextureToShader(Texture texture, int textureUnit, const std::string& uniformName) override;
    void setShaderParameters(...) override;
    void renderMesh(Mesh mesh, ...) override;
    void setRenderTarget(RenderTarget target) override;
    void clearRenderTarget(...) override;
    void beginFrame() override;
    void endFrame() override;
    void resizeViewport(...) override;
    GPUInfo queryCapabilities() override;
    void displayCapabilities() override;
    std::string getError() override;
};

