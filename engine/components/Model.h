#pragma once

#include "Component.h"
#include "meshes/Mesh.h"
#include "colliders/Collider.h"

class Model : public Component {

public:

    Mesh *mesh;
    Collider *collider;

    ObjectType getType() override {
        return ObjectType::OT_Model;
    };

    static Model *createFromGeometry(Geometry::ShapeType shape, GeometryConfig config = {});

    // todo setCollidable(level) radial, box, mesh
    void setCollidable() {
        collider = new Collider();
        // get box of meshes
        // getRadius of mesh
    }

};


