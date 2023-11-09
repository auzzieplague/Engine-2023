#include "RenderTarget.h"
#include <GraphicsAPI.h>
#include <graphics/buffers/FrameBuffer.h>

#include <utility>

GraphicsAPI *RenderTarget::graphicsApi;

void RenderTarget::setGraphicsAPI(GraphicsAPI *api) {
    RenderTarget::graphicsApi = api;
}

RenderTarget *RenderTarget::setClearColour(const glm::vec4 &colour) {
    this->clearColour = colour;
    return this;
}

RenderTarget *RenderTarget::initialise() {
    if (this->frameBuffer != nullptr) {
        delete this->frameBuffer;
    }

    this->frameBuffer = new FrameBuffer(this->width, this->height);
    this->frameBuffer->generate();
    return this;
}

RenderTarget::RenderTarget( int height,  int width) : height(height), width(width) {
    this->initialise();
}

RenderTarget *RenderTarget::finalRender() {
    RenderTarget::graphicsApi->finalRender(this);
    return this;
}

RenderTarget *RenderTarget::bind() {
    RenderTarget::graphicsApi->renderTargetBind(this);
    return this;
}

RenderTarget *RenderTarget::clearDepthBuffer(bool doBind) {
    if (doBind) {
        this->bind();
    }
    RenderTarget::graphicsApi->renderTargetClearDepthBuffer(this);
    return this;
}

RenderTarget *RenderTarget::clearColourBuffer(bool doBind) {
    if (doBind) {
        this->bind();
    }
    RenderTarget::graphicsApi->renderTargetClearColourBuffer(this);
    return this;
}

RenderTarget *RenderTarget::renderMeshes(std::vector<MeshData *> meshData, bool doBind) {
    if (doBind) {
        this->bind();
    }
    RenderTarget::graphicsApi->renderTargetDrawMeshData(this, std::move(meshData));
    return this;
}
