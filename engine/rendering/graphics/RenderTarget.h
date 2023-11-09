#pragma once

#include <string>
#include <glm/glm.hpp>
#include <vector>
#include "Texture.h"

class GraphicsAPI;

class DepthBuffer;

class StencilBuffer;

class FrameBuffer;

class MeshData;

class RenderTarget {
public:
    std::string name = "render target"; // could use object name if inheriting from object.
    glm::vec4 clearColour{1, 1, 1, 1};
    DepthBuffer *depthBuffer = nullptr;
    float clearDepth = 1.0;
    StencilBuffer *stencilBuffer = nullptr;
    float clearStencil = 0;
    unsigned int samplesPerPixel = 8;

    int height = 720; // also stored on framebuffer - might remove here and replace with getters
    int width = 1024;
    FrameBuffer *frameBuffer = nullptr;

    static GraphicsAPI *graphicsApi;

    static void setGraphicsAPI(GraphicsAPI *api);

    RenderTarget(int height, int width);

    RenderTarget *setClearColour(const glm::vec4 &clearColour);

    RenderTarget *initialise();

    // doBind allows us to only bind once where necessary
    RenderTarget *bind();

    RenderTarget *clearDepthBuffer(bool doBind = false);

    RenderTarget *clearColourBuffer(bool doBind = false);

    RenderTarget *renderMeshes(std::vector<MeshData *>, bool doBind = false);

    RenderTarget *finalRender();


};

