#pragma once

#include "BaseBuffer.h"

class GraphicsAPI; // forward declare

class IndexBuffer: public BaseBuffer {


public:
    IndexBuffer(BufferContainer * VAO, const unsigned int *data, size_t dataSize, const char* usage): BaseBuffer(data, dataSize, usage){
        this->containerObject = VAO;
    };
    explicit IndexBuffer(BufferContainer * VAO, MeshData * meshData, const char *usage);

    IndexBuffer* generate() override;
    IndexBuffer* bind() override;
};