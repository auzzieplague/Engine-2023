#include "IndexBuffer.h"
#include <GraphicsAPI.h> // override forward declaration of graphics api here

GraphicsAPI * IndexBuffer::graphicsApi;

IndexBuffer *IndexBuffer::generate() {
    graphicsApi->createIndexBuffer(this);
    return this;
}

IndexBuffer *IndexBuffer::bind() {
    graphicsApi->bindIndexBuffer(this);
    return this;
}
