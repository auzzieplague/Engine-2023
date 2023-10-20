#include "VertexBuffer.h"
#include <GraphicsAPI.h> // override forward declaration of graphics api here


VertexBuffer* VertexBuffer::generate() {
    graphicsApi->createVertexBuffer(this);
    return this;
}


VertexBuffer* VertexBuffer::bind() {
    graphicsApi->bindVertexBuffer(this);
    return this;
}


