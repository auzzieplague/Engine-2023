#pragma once

#include "Component.h"
#include "meshes/Mesh.h"
#include "meshes/CollisionMesh.h"

class Model: public Component {

    // primary focus on collision mesh

    CollisionMesh collisionMesh;
    void setCollisionMesh(Mesh meshToUse, glm::vec3 offset={0,0,0}, glm::vec3 scale={0,0,0});

    // also materials, meshes with submeshes and animation.
    // mesh needs the material association
};


