#pragma once

#include <glm/gtc/quaternion.hpp>
#include "Mesh.h"

class CollisionMesh : public Mesh {
private:
    enum CollisionMeshType {
        Box,
        Sphere,
        Capsule,
        Mesh,
        ConvexMesh
    };

    CollisionMeshType meshType;
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;

public:
////    CollisionMesh(CollisionMeshType type, glm::vec3 pos, glm::quat rot, glm::vec3 scl) :
////            meshType(type), position(pos), rotation(rot), scale(scl) {}
//
//    void updatePosition(glm::vec3 newPos) {
//        position = newPos;
//    }
//
//    void updateRotation(glm::quat newRot) {
//        rotation = newRot;
//    }
//
//    void updateScale(glm::vec3 newScale) {
//        scale = newScale;
//    }
//
//    bool intersects(const CollisionMesh& otherMesh) const {
//        // Check if this collision mesh intersects with another collision mesh
//        // The method for doing this will depend on the specific mesh type
//        // For example, if both meshes are boxes, we might use an AABB collision detection algorithm
//        // If one or both meshes are more complex (such as a mesh or convex mesh), we might use a more advanced collision detection algorithm
//        return false; // Return true if the meshes intersect, false otherwise
//    }

};

