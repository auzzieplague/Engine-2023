#include <iostream>
#include "Transform.h"

Transform::Transform() :
        mPosition(glm::vec3(0.0f)),
        mRotation(glm::quat()),
        mScale(glm::vec3(1.0f)) {}

glm::vec3 Transform::getPosition() const {
    return mPosition;
}

glm::quat Transform::getRotation() const {
    return mRotation;
}

glm::vec3 Transform::getScale() const {
    return mScale;
}

glm::mat4 Transform::getMatrix()  {
    // if not dirty can probably return last result rather than recalc
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), mPosition);
    glm::mat4 rotationMatrix = glm::mat4_cast(mRotation);
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), mScale);
    return translationMatrix * rotationMatrix * scaleMatrix;
}

void Transform::setPosition(glm::vec3 position) {
    this->mPosition = position;
}

glm::quat toQuaternion(const glm::vec3& euler) {
    glm::quat q;
    q = glm::angleAxis(glm::radians(euler.z), glm::vec3(0, 0, 1));
    q = glm::angleAxis(glm::radians(euler.y), glm::vec3(0, 1, 0)) * q;
    q = glm::angleAxis(glm::radians(euler.x), glm::vec3(1, 0, 0)) * q;
    return q;
}

void Transform::setRotation(glm::vec3 rotation) {
    this->mRotation = toQuaternion(rotation);
}

void Transform::setRotation(glm::quat rotation) {
    this->mRotation = rotation;
}

void Transform::setScale(glm::vec3 scale) {
    this->mScale = scale;
}

[[maybe_unused]] void Transform::translate(glm::vec3 translation) {
    mPosition += translation;
}

void Transform::rotateAxis(glm::vec3 axis, float angle) {
    mRotation = glm::rotate(mRotation, angle, axis);
}

void Transform::scale(glm::vec3 scale) {
    this->mScale *= scale;
}

physx::PxTransform Transform::getPxTransform() const {
// Scale is not supported - has to be adjusted when creating shape / mesh
    physx::PxTransform t(
            physx::PxVec3(mPosition.x, mPosition.y, mPosition.z),
    physx::PxQuat(mRotation.x, mRotation.y, mRotation.z, mRotation.w)
            );
    return t;

}

void Transform::setFromMatrix(const glm::mat4 &matrix) {
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(matrix, mScale, mRotation, mPosition, skew, perspective);
}

