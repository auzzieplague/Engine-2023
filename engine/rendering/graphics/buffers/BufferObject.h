#pragma once

#include "BaseBuffer.h"
#include "graphics/GPULayout.h"

class BufferObject: public BaseBuffer {
public:

//    std::vector<GPULayout *> layouts;
    std::map<unsigned int, GPULayout *> layouts;

    BufferObject(): BaseBuffer(nullptr, 0, nullptr){}

    BufferObject *generate() override;

    BufferObject *bind() override;

    BufferObject * addLayout(GPULayout * layout) {
        layouts[layout->index] = layout;
        return this;
    }
};

