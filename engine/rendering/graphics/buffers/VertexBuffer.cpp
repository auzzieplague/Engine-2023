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

VertexBuffer::VertexBuffer(MeshData *meshData, const char *usage) {
    this->data=meshData->m_vertices.data();
    this->byteCount = meshData->m_vertices.size() * 3 * sizeof(float); // bytes
    if (usage) {
        this->usage = graphicsApi->getFlag(usage);
    }
};


