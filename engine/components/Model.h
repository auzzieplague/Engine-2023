#pragma once

#include "Component.h"
#include "meshes/Mesh.h"
#include "Collider.h"

class Model: public Component {

public:

    ObjectType getType() override {
        return ObjectType::OT_Model;
    };

    static Model * createFromGeometry(Geometry::ShapeType shape){
        auto *model = new Model();
        switch(shape) {
            default:
                Debug::show("unsupported shape requested by model");
                break;
            case Geometry::ShapeType::Cube :
                break;
        }
    }

    Collider *collider;
    Mesh *mesh;
};


