#pragma once

#include "BaseBuffer.h"
#include "graphics/VertexAttribute.h"

class BufferContainer: public BaseBuffer {
public:

    std::map<unsigned int, VertexAttribute *> attributes;

    BufferContainer(): BaseBuffer(nullptr, 0, nullptr){}

    BufferContainer *generate() override; // allocates resources on GPU

    BufferContainer *bind() override;

    BufferContainer * addAttribute(VertexAttribute * attribute) {
        attributes[attribute->index] = attribute;
        return this;
    }

    BufferContainer *linkToMeshData(MeshData * meshData) {
        meshData->m_gID = this->bufferID; // legacy implementation
//        meshData->bufferContainer = this; // new Implementation
        return this;
    };
};

