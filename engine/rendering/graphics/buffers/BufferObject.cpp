#include "BufferObject.h"
#include <GraphicsAPI.h> // override forward declaration of graphics api here

BufferObject *BufferObject::generate() {
    graphicsApi->createBufferObject(this);
    return this;
}

BufferObject *BufferObject::bind() {
    graphicsApi->bindBufferObject(this);
    return this;
}

