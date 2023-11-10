#pragma once

#include "BaseBuffer.h"

class GraphicsAPI; // forward declare

class IndexBuffer: public BaseBuffer {


public:
    IndexBuffer(const unsigned int *data, size_t dataSize, const char* usage): BaseBuffer(data,dataSize,usage){};
    explicit IndexBuffer(MeshData * meshData, const char *usage);

    IndexBuffer* generate() override;
    IndexBuffer* bind() override;
};