#include "IndexBuffer.h"
#include <GraphicsAPI.h> // override forward declaration of graphics api here

IndexBuffer *IndexBuffer::generate() {
    graphicsApi->createIndexBuffer(this);
    return this;
}

IndexBuffer *IndexBuffer::bind() {
    graphicsApi->bindIndexBuffer(this);
    return this;
}

IndexBuffer::IndexBuffer(BufferContainer * VAO, MeshData *meshData, const char *usage)  {
    this->data = meshData->m_indices.data();
    this->byteCount = meshData->m_indices.size() * sizeof(unsigned int);
    if (usage) {
        this->usage = graphicsApi->getFlag(usage);
    }
    this->containerObject = VAO;


}