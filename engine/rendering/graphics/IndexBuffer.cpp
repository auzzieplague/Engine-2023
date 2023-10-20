#include "IndexBuffer.h"
#include <GraphicsAPI.h> // override forward declaration of graphics api here

GraphicsAPI * IndexBuffer::graphicsApi;

void IndexBuffer::setGraphicsAPI(GraphicsAPI *api) {
    IndexBuffer::graphicsApi = api;
}

IndexBuffer *IndexBuffer::generate() {
    graphicsApi->createIndexBuffer(this);
    return this;
}

IndexBuffer *IndexBuffer::bind() {
    graphicsApi->bindIndexBuffer(this);
    return this;
}

IndexBuffer::IndexBuffer(const unsigned int *data, size_t dataSize, const char *usage) {

}
