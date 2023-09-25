#pragma once

#include <GraphicsLayer.h>
#include <graphics/VertexBuffer.h>
#include <graphics/IndexBuffer.h>
#include <graphics/Texture.h>
#include <graphics/Shader.h>
#include <graphics/RenderTarget.h>
#include <GPUInfo.h>

class Mesh;

class GraphicsAPI {
public:
    virtual bool initialise() {return false;};
    virtual void shutdown() = 0;
    virtual VertexBuffer createVertexBuffer(...) = 0;
    virtual IndexBuffer createIndexBuffer(...) = 0;
    virtual Texture loadTexture(...) = 0;
    virtual Mesh loadMesh(...) = 0;
    virtual Shader createShader(...) = 0;
    virtual void setShader(Shader shader) = 0;
    virtual void setUniform(...) = 0;
    virtual void bindTextureToShader(Texture texture, int textureUnit, const std::string& uniformName) = 0;
    virtual void setShaderParameters(...) = 0;
    virtual void renderMesh(Mesh mesh, ...) = 0;
    virtual void setRenderTarget(RenderTarget target) = 0;
    virtual void clearRenderTarget(...) = 0;
    virtual void beginFrame() = 0;
    virtual void endFrame() = 0;
    virtual void resizeViewport(...) = 0;
    virtual GPUInfo queryCapabilities() = 0;
    virtual void displayCapabilities() = 0;
    virtual std::string getError() = 0;
};




