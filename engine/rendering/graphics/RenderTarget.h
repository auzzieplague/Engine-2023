#pragma once

#include <string>

class GraphicsAPI;

class DepthBuffer;

class StencilBuffer;

class RenderTarget {
public:
    std::string name = "render target"; // could use object name if inheriting from object.
    unsigned int width = 512;
    unsigned int height = 512;
//    glm::vec4 clearColour{1, 1, 1, 1};
    DepthBuffer *depthBuffer = nullptr;
    float clearDepth = 1.0;
    StencilBuffer *stencilBuffer = nullptr;
    float clearStencil = 0;
    unsigned int samplesPerPixel = 8;

    void *target;

    static GraphicsAPI *graphicsApi;

    static void setGraphicsAPI(GraphicsAPI *api);

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
};

