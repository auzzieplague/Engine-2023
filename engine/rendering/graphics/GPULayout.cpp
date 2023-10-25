
#include "GPULayout.h"
#include <GraphicsBehaviour.h>
#include "BufferObject.h"

GraphicsAPI *GPULayout::graphicsApi;

GPULayout *GPULayout::apply(BufferObject *buffer) {
    graphicsApi->applyLayout(this, buffer);
    return this;
}
