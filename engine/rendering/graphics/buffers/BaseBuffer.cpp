
#include "BaseBuffer.h"
#include <GraphicsAPI.h> // override forward declaration of graphics api here

GraphicsAPI * BaseBuffer::graphicsApi;

void BaseBuffer::setGraphicsAPI(GraphicsAPI *api) {
    BaseBuffer::graphicsApi = api;
}

BaseBuffer::BaseBuffer(const void *data, size_t dataSize, const char* usage) {
    this->data = data;
    this->byteCount = dataSize;
    if (usage) {
        this->usage = graphicsApi->getFlag(usage);
    }
}