#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <physx/PxPhysicsAPI.h>

class Transform {
private:
    glm::vec3 m_position{};
    glm::quat m_rotation{0.01f,0.01f,0.01f,0.01f};
    glm::vec3 m_scale{};
public:
    Transform();

    [[nodiscard]] glm::vec3 getPosition() const;

    [[nodiscard]] glm::quat getRotation() const;

    [[nodiscard]] glm::vec3 getScale() const;

    [[nodiscard]] glm::mat4 getMatrix();

    void setPosition(glm::vec3 position);

    void setRotation(glm::vec3 rotation);

    void setScale(glm::vec3 scale);

    [[maybe_unused]] [[maybe_unused]] void translate(glm::vec3 translation);

    void rotate(glm::vec3 axis, float angle);

    void scale(glm::vec3 scaleFactor);

    void applyPxTransform(const physx::PxTransform& pxTransform) {
        /// scale is not a function of physx - rotation and position only
        // Extract the position, rotation, and scale from the PxTransform
        physx::PxVec3 pxPosition = pxTransform.p;
        physx::PxQuat pxRotation = pxTransform.q;
//        auto pxScale = physx::PxVec3(1.0f);  // Default scale of 1.0f

        // Convert the PhysX types to the equivalent glm types
        glm::vec3 position = glm::vec3(pxPosition.x, pxPosition.y, pxPosition.z);
        glm::quat rotation = glm::quat(pxRotation.w, pxRotation.x, pxRotation.y, pxRotation.z);
//        glm::vec3 scale = glm::vec3(pxScale.x, pxScale.y, pxScale.z);

        // Update the position, rotation, and scale properties of the Transform object
        m_position = position;
        m_rotation = rotation;
//        m_scale = scale;
    }


    void rotateX(float degrees) {
        float radians = glm::radians(degrees);
        glm::quat rotation = glm::angleAxis(radians, glm::vec3(1, 0, 0));
        m_rotation = rotation * m_rotation;
    }

    void rotateY(float degrees) {
        float radians = glm::radians(degrees);
        glm::quat rotation = glm::angleAxis(radians, glm::vec3(0, 1, 0));
        m_rotation = rotation * m_rotation;
    }

    void rotateZ(float degrees) {
        float radians = glm::radians(degrees);
        glm::quat rotation = glm::angleAxis(radians, glm::vec3(0, 0, 1));
        m_rotation = rotation * m_rotation;
    }

    physx::PxTransform getPxTransform() const;
};