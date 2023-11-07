#pragma once

#include <string>
#include <glm/glm.hpp>
#include "Texture.h"

class GraphicsAPI;
class DepthBuffer;
class StencilBuffer;
class FrameBuffer;

class RenderTarget {
public:
    std::string name = "render target"; // could use object name if inheriting from object.
    glm::vec4 clearColour{1, 1, 1, 1};
    DepthBuffer *depthBuffer = nullptr;
    float clearDepth = 1.0;
    StencilBuffer *stencilBuffer = nullptr;
    float clearStencil = 0;
    unsigned int samplesPerPixel = 8;

    unsigned int height = 720; // also stored on framebuffer - might remove here and replace with getters
    unsigned int width = 1024;
    FrameBuffer *frameBuffer = nullptr;
//    Texture * texture; // will be on framebuffer

//    void *target;

    static GraphicsAPI *graphicsApi;
    static void setGraphicsAPI(GraphicsAPI *api);

    RenderTarget(unsigned int height, unsigned int width);

    RenderTarget * setClearColour(const glm::vec4 &clearColour);
    RenderTarget * initialise(int width, int height);
//    RenderTarget * clearTarget();


//    RenderTarget();
//    ~RenderTarget();
//
//    void initialize(int width, int height);
//    void bind();
//    void unbind();
//    void attachColorTexture(const Texture& texture);
//    void attachDepthTexture(const Texture& texture);
//    bool isComplete();
//    void release();
    RenderTarget * makeCurrent();
};

