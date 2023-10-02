
#include <graphics/VertexBuffer.h>
#include <graphics/IndexBuffer.h>
#include <graphics/Texture.h>
#include <graphics/Shader.h>
#include <graphics/RenderTarget.h>
#include <GPUInfo.h>
#include <cstdio>

class GraphicsBehaviour {

protected:
    GPUInfo *gpuInfo{};
public:
// Initialization
    virtual bool initialise(...) { return false; };
    virtual void queryCapabilities(...) {  };
    virtual void displayCapabilities(...);

    // Resource Management
    virtual unsigned int createVertexBuffer(const VertexBuffer& vertexBuffer, ...) {return 0;};
    virtual unsigned int createIndexBuffer(...) {return 0;};
    virtual unsigned int createTexture(...) {return 0;};
    virtual unsigned int createShaderProgram(...) {return 0;};

    // Rendering
    virtual void bindVertexBuffer(...) {};
    virtual void bindIndexBuffer(...) {};
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
};
