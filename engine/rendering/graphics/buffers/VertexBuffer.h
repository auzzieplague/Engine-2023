#pragma once

#include "BaseBuffer.h"

class VertexBuffer: public BaseBuffer {

public:
    VertexBuffer(BufferContainer* VAO, const void *data, size_t dataSize, const char *usage): BaseBuffer(data, dataSize, usage ){
        this->containerObject = VAO;
    };

    // todo usage might be applied on the mesh
    VertexBuffer(BufferContainer* VAO, MeshData * meshData, const char *usage);

    VertexBuffer* generate() override;
    VertexBuffer* bind() override;
};
