#pragma once

#include "../core/Base.h"

class Object {
public:

    enum class ObjectType {
        OT_Unknown,
        OT_Object,
        OT_Component,
        OT_Model,
        OT_Terrain,
        OT_Mesh,
        OT_Texture,
        OT_Light6
    };

    virtual ObjectType getType() {
        return ObjectType::OT_Object;
    };

    virtual std::string getName() {
        return "unknown Object";
    };


};

