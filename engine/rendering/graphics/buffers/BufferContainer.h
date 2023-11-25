#pragma once

#include "BaseBuffer.h"
#include "graphics/VertexAttribute.h"

class BufferContainer: public BaseBuffer {
public:

    std::map<unsigned int, VertexAttribute *> attributes;

    BufferContainer(): BaseBuffer(nullptr, 0, nullptr){}

    BufferContainer *generate() override;

    BufferContainer *bind() override;

    BufferContainer * addLayout(VertexAttribute * attribute) {
        attributes[attribute->index] = attribute;
        return this;
    }

    BufferContainer *forMeshData(MeshData * meshData) {
        meshData->m_gID = this->bufferID; // legacy implementation
        meshData->bufferContainer = this; // new Implementation
        return this;
    };
};

