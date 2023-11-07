#include "RenderTarget.h"
#include <GraphicsAPI.h>
#include <graphics/buffers/FrameBuffer.h>

GraphicsAPI *RenderTarget::graphicsApi;

void RenderTarget::setGraphicsAPI(GraphicsAPI *api) {
    RenderTarget::graphicsApi = api;
}

RenderTarget *RenderTarget::setClearColour(const glm::vec4 &colour) {
    this->clearColour = colour;
    return this;
}

RenderTarget *RenderTarget::makeCurrent() {
    // todo: set this render target to be the current render target for the api
    return this;
}

RenderTarget *RenderTarget::initialise(int width, int height) {
    if (this->frameBuffer) {
        delete this->frameBuffer;
    }

    this->frameBuffer = new FrameBuffer(width, height);
    this->width = width;
    this->height = height;

    return this;
}

RenderTarget::RenderTarget(unsigned int height, unsigned int width) : height(height), width(width) {

}

