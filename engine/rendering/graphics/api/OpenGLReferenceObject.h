#pragma once

#include "GraphicsInterfaceReferenceObject.h"

class OpenGLReferenceObject: public GraphicsInterfaceReferenceObject {
public:
    // for open gl this should contain the VOA and any other opengl specific data.
    unsigned int VAO=0;

    void test() override{
        std::cout << "child class";
    }
};
