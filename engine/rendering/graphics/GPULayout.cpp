
#include "GPULayout.h"
#include <GraphicsBehaviour.h>
#include "graphics/buffers/BufferObject.h"

GraphicsAPI *GPULayout::graphicsApi;

GPULayout *GPULayout::applyTo(BufferObject *buffer) {
    this->applyToBuffer = buffer;
    graphicsApi->applyLayout(this);
    return this;
}

void GPULayout::setGraphicsAPI(GraphicsAPI *api) {
    GPULayout::graphicsApi = api;
}