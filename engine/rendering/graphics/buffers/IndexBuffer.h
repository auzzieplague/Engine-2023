#pragma once

#include "BaseBuffer.h"

class GraphicsAPI; // forward declare

class IndexBuffer: public BaseBuffer {


public:
    IndexBuffer(const unsigned int *data, size_t dataSize, const char* usage): BaseBuffer(data,dataSize,usage){};

    IndexBuffer* generate() override;
    IndexBuffer* bind() override;
};