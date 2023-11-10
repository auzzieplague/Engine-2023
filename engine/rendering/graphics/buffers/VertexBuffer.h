#pragma once

#include "BaseBuffer.h"

class VertexBuffer: public BaseBuffer {

public:
    VertexBuffer(const void *data, size_t dataSize, const char *usage): BaseBuffer(data, dataSize,usage ){};

    // todo usage might be applied on the mesh
    VertexBuffer(MeshData * meshData, const char *usage);

    VertexBuffer* generate() override;
    VertexBuffer* bind() override;
};
