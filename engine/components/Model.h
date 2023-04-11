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
        //note: model would need to be set collidable before adding to scene, to be added to correct <vector>
        collider = new Collider();
        collider->aabb.findMinMaxCorners(mesh->positions);
        collider->sphere.findRadiusAndCenter(mesh->positions);
        // get box of meshes
        // getRadius of meshes
    }
};


