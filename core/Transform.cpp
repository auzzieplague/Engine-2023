#include <iostream>
#include "Transform.h"

Transform::Transform() :
        m_position(glm::vec3(0.0f)),
        m_rotation(glm::quat()),
        m_scale(glm::vec3(1.0f)) {}

glm::vec3 Transform::getPosition() const {
    return m_position;
}

glm::quat Transform::getRotation() const {
    return m_rotation;
}

glm::vec3 Transform::getScale() const {
    return m_scale;
}

// todo = rename, nothing to do with a model at this point
glm::mat4 Transform::getModelMatrix() const {
    // if not dirty can probably return last result rather than recalc
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), m_position);
    glm::mat4 rotationMatrix = glm::mat4_cast(m_rotation);
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), m_scale);
    return translationMatrix * rotationMatrix * scaleMatrix;
}

void Transform::setPosition(glm::vec3 position) {
    this->m_position = position;
}

void Transform::setRotation(glm::quat rotation) {
    this->m_rotation = rotation;
}

void Transform::setScale(glm::vec3 scale) {
    this->m_scale = scale;
}

[[maybe_unused]] void Transform::translate(glm::vec3 translation) {
    m_position += translation;
}

void Transform::rotate(glm::vec3 axis, float angle) {
    m_rotation = glm::rotate(m_rotation, angle, axis);
}

void Transform::scale(glm::vec3 scale) {
    this->m_scale *= scale;
}

physx::PxTransform Transform::getPxTransform() const {
// Scale is not supported - has to be adjusted when creating shape / mesh
    physx::PxTransform t(
            physx::PxVec3(m_position.x,m_position.y,m_position.z),
    physx::PxQuat(m_rotation.x,m_rotation.y,m_rotation.z,m_rotation.w)
            );

//   /
    return t;

}
