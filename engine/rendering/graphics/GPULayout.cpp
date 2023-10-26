
#include "GPULayout.h"
#include <GraphicsBehaviour.h>
#include "BufferObject.h"

GraphicsAPI *GPULayout::graphicsApi;

GPULayout *GPULayout::apply(BufferObject *buffer) {
    this->applyToBuffer = buffer;
    graphicsApi->applyLayout(this);
    return this;
}

void GPULayout::setGraphicsAPI(GraphicsAPI *api) {
    GPULayout::graphicsApi = api;
}