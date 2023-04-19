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

    // todo setCollider(level) radial, box, mesh
    void setCollider();

    /**
     * use model->setPostion to correctly update colliders and underlying objects
     */
    void setPosition(glm::vec3) override;

    void setScale(glm::vec3) override;

    void setRotation(glm::vec3) override;
};


