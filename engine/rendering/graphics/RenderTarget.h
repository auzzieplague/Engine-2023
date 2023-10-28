#pragma once

#include <string>
#include <glm/glm.hpp>
class GraphicsAPI;

class DepthBuffer;

class StencilBuffer;



class RenderTarget {
public:
    std::string name = "render target"; // could use object name if inheriting from object.
    unsigned int width = 512;
    unsigned int height = 512;
    glm::vec4 clearColour{1, 1, 1, 1};
    DepthBuffer *depthBuffer = nullptr;
    float clearDepth = 1.0;
    StencilBuffer *stencilBuffer = nullptr;
    float clearStencil = 0;
    unsigned int samplesPerPixel = 8;

    void *target;

    static GraphicsAPI *graphicsApi;
    static void setGraphicsAPI(GraphicsAPI *api);

    void setClearColour(const glm::vec4 &clearColour);
    void initialise(int width, int height);
    void clearTarget();


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

