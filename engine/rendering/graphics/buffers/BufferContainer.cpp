#include "BufferContainer.h"
#include <GraphicsAPI.h> // override forward declaration of graphics api here

BufferContainer *BufferContainer::generate() {
    graphicsApi->createContainerObject(this);
    return this;
}

BufferContainer *BufferContainer::bind() {
    graphicsApi->bindContainerObject(this);
    return this;
}

