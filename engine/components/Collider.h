#include <glm/glm.hpp>
#include <vector>
#include "Geometry.h"

class Collider {
public:
    enum ColliderType {
        Box,
        Sphere,
        Capsule,
        Mesh,
        ConvexMesh
    };

    std::vector<glm::vec3> m_vertices;
    ColliderType collisionType;

    Collider() = default;

    Collider * Factory(ColliderType type) {

        auto collider = new Collider();
        Geometry g;
        switch (type){
            case Box:
                g.buildCube();
                collider->setVertices(g.positions);
                break;
            case Sphere:
                break;
            case Capsule:
                break;
            case Mesh:
                break;
            case ConvexMesh:
                break;
        }

        return collider;
    }

    // Constructor that takes in a list of vertices
    Collider(const std::vector<glm::vec3>& vertices)
            : m_vertices(vertices) {}

    // Getters and setters
    void setVertices(const std::vector<glm::vec3>& vertices) { m_vertices = vertices; }
    [[nodiscard]] const std::vector<glm::vec3>& getVertices() const { return m_vertices; }

    // Check if a given point is inside the collider
    bool containsPoint(const glm::vec3& point) const;

};