
#include "VertexAttribute.h"
#include "graphics/buffers/BufferContainer.h"

GraphicsAPI *VertexAttribute::graphicsApi;

VertexAttribute *VertexAttribute::applyTo(BufferContainer *buffer) {
    this->applyToBuffer = buffer;
    buffer->addAttribute(this);
    return this;
}

void VertexAttribute::setGraphicsAPI(GraphicsAPI *api) {
    VertexAttribute::graphicsApi = api;
}