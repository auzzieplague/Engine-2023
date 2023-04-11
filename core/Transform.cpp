#include "Transform.h"

Transform::Transform() :
        position(glm::vec3(0.0f)),
        rotation(glm::quat()),
        scaleVec(glm::vec3(1.0f)) {}

glm::vec3 Transform::getPosition() const {
    return position;
}

glm::quat Transform::getRotation() const {
    return rotation;
}

glm::vec3 Transform::getScale() const {
    return scaleVec;
}

glm::mat4 Transform::getModelMatrix() const {
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
    glm::mat4 rotationMatrix = glm::mat4_cast(rotation);
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scaleVec);
    return translationMatrix * rotationMatrix * scaleMatrix;
}

void Transform::setPosition(glm::vec3 position) {
    this->position = position;
}

void Transform::setRotation(glm::quat rotation) {
    this->rotation = rotation;
}

void Transform::setScale(glm::vec3 scale) {
    this->scaleVec = scale;
}

void Transform::translate(glm::vec3 translation) {
    position += translation;
}

void Transform::rotate(glm::vec3 axis, float angle) {
    rotation = glm::rotate(rotation, angle, axis);
}

void Transform::scale(glm::vec3 scale) {
    this->scaleVec *= scale;
}
