#pragma once

#include "BaseBuffer.h"

class BufferObject: public BaseBuffer {
public:

    BufferObject(): BaseBuffer(nullptr, 0, nullptr){}

    BufferObject *generate() override;

    BufferObject *bind() override;

};

