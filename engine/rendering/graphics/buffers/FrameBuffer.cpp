#include "FrameBuffer.h"
#include <GraphicsAPI.h> // override forward declaration of graphics api here

GraphicsAPI * FrameBuffer::graphicsApi;

void FrameBuffer::setGraphicsAPI(GraphicsAPI *api) {
    FrameBuffer::graphicsApi = api;
}

FrameBuffer *FrameBuffer::generate() {
    graphicsApi->createFrameBuffer(this);
    return this;
}
