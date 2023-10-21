#pragma once

#include "BaseBuffer.h"
#include "GPULayout.h"

class BufferObject: public BaseBuffer {
public:

    std::vector<GPULayout *> layouts;

    BufferObject(): BaseBuffer(nullptr, 0, nullptr){}

    BufferObject *generate() override;

    BufferObject *bind() override;

    GPULayout * addLayout(GPULayout * layout) const{
        // todo graphicsAPI add layout
//        this.layouts->push_back(layout);
        return layout;
    }

};

