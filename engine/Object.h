#pragma once
#include "../core/Base.h"

class Object {
public:

    enum class ObjectType {
        OT_Object = 1,
        OT_Component = 2,
        OT_Model = 3,
        OT_Mesh = 4,
        OT_Texture = 5,
        OT_Light = 6
    };

    virtual ObjectType getType() {
        return ObjectType::OT_Object;
    };

    virtual std::string getName() {
        return "unknown Object";
    };


};

