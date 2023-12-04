#pragma once

#include <iostream>

class GraphicsInterfaceReferenceObject {
public:
    virtual void test(){
        std::cout << "base object";
    }
};
