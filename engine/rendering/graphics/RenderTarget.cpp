#include "RenderTarget.h"
#include <GraphicsAPI.h>

GraphicsAPI * RenderTarget::graphicsApi;

void RenderTarget::setGraphicsAPI(GraphicsAPI *api) {
    RenderTarget::graphicsApi = api;
}

void RenderTarget::setClearColour(const glm::vec4 &colour) {
    this->clearColour = colour;
}

