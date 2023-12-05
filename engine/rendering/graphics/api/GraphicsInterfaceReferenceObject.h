#pragma once

#include <iostream>
#include <Debug.h>

class GraphicsInterfaceReferenceObject {
public:
    virtual void test(){
        Debug::show("base object");
    }
};
