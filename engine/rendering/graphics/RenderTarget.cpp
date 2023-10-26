#include "RenderTarget.h"
#include <GraphicsAPI.h>

GraphicsAPI * RenderTarget::graphicsApi;

void RenderTarget::setGraphicsAPI(GraphicsAPI *api) {
    RenderTarget::graphicsApi = api;
}
