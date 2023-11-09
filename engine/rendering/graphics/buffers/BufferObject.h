#pragma once

#include "BaseBuffer.h"
#include "graphics/GPULayout.h"

class BufferObject: public BaseBuffer {
public:

    std::map<unsigned int, GPULayout *> layouts;

    BufferObject(): BaseBuffer(nullptr, 0, nullptr){}

    BufferObject *generate() override;

    BufferObject *bind() override;

    BufferObject * addLayout(GPULayout * layout) {
        layouts[layout->index] = layout;
        return this;
    }

    BufferObject *forMeshData(MeshData * meshData) {
        meshData->m_gID = this->bufferID; // legacy implementation
        meshData->bufferObject = this; // new Implementation
        return this;
    };
};

