#include "VertexBuffer.h"
#include <GraphicsAPI.h> // override forward declaration of graphics api here

GraphicsAPI *VertexBuffer::graphicsApi = nullptr;

void VertexBuffer::setGraphicsAPI(GraphicsAPI *api) {
    VertexBuffer::graphicsApi = api;
}

VertexBuffer* VertexBuffer::generate() {
    graphicsApi->createVertexBuffer(this);
    return this;
}


VertexBuffer* VertexBuffer::bind() {
    graphicsApi->bindVertexBuffer(this);
    return this;
}

VertexBuffer::VertexBuffer(const void *data, size_t dataSize, const char* usage) {
    this->data = data;
    this->dataSize = dataSize;
    this->usage = graphicsApi->getFlag(usage);
}
