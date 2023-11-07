#include "FrameBuffer.h"
#include <GraphicsAPI.h> // override forward declaration of graphics api here

FrameBuffer *FrameBuffer::generate() {
    graphicsApi->createFrameBuffer(this);
    return this;
}
