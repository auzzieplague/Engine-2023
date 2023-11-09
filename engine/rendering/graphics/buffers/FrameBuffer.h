#pragma once

#include "BaseBuffer.h"

class GraphicsAPI;

class FrameBuffer : public BaseBuffer {

public:
    int height;
    int width;

    FrameBuffer (int width, int height): BaseBuffer(nullptr,0,""){
        this->width = width;
        this->height = height;
    };

    FrameBuffer* generate() override;

    Texture * texture{};
};
