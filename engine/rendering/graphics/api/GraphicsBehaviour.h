#pragma once
#include <graphics/Texture.h>
#include <graphics/Shader.h>
#include <graphics/RenderTarget.h>
#include <GPUInfo.h>
#include <cstdio>

class VertexBuffer;
class IndexBuffer;
class BufferObject;

class GraphicsBehaviour {

protected:
    GPUInfo *gpuInfo{};
public:
// Initialization
    virtual bool initialise(...) { return false; };
    virtual void queryCapabilities(...) {  };
    virtual void displayCapabilities(...);

    // Resource Management
    virtual unsigned int createVertexBuffer(VertexBuffer* vb) {return 0;};
    virtual unsigned int createIndexBuffer(IndexBuffer *ib) {return 0;};
    virtual unsigned int createBufferObject(BufferObject *bo) {return 0;}; // VAO in opengl

    virtual unsigned int createTexture(...) {return 0;};
    virtual unsigned int createShaderProgram(...) {return 0;};

    // Rendering
    virtual void bindVertexBuffer(VertexBuffer* vb) {};
    virtual void bindIndexBuffer(IndexBuffer* ib) {};
    virtual void bindBufferObject(BufferObject *bo) {}; // VAO in opengl

    virtual void bindTexture(...) {};
    virtual void bindShaderProgram(...) {};
    virtual void drawIndexed(...) {};
    virtual void setUniforms(...) {};

    // Framebuffer and Render Target Management
    virtual void setRenderTarget(...) {};
    virtual void clearRenderTarget(...) {};

    // Viewport and Projection
    virtual void setViewport(...) {};
    virtual void setProjectionMatrix(...) {};
    virtual void resizeViewport(...) {};

    // Shader Management
    virtual void compileShader(...) {};
    virtual void linkProgram(...) {};

    // Cleanup and Shutdown
    virtual void shutdown(...) {};
    virtual void demoTriangle(...) {};

    virtual unsigned int getFlagCode(const char *string);
};
