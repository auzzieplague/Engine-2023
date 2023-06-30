#include "Component.h"

void Component::setLocalPosition(glm::vec3 newPosition) {
    this->localTransform.setPosition(newPosition);
}

void Component::setLocalRotation(glm::vec3 newRotation) {
    this->localTransform.setRotation(newRotation);
}

void Component::rotate(glm::vec3 newRotation) {
    this->localTransform.rotate(newRotation);
}

void Component::scale(float scale) {
    this->scale(glm::vec3(scale));
}

void Component::scale(glm::vec3 scale) {
    this->localTransform.scale(scale);
}

void Component::setLocalScale(glm::vec3 newScale) {
    this->localTransform.setScale(newScale);
}

void Component::setLocalRotation(glm::quat rotation) {
    this->localTransform.setRotation(rotation);
}

glm::vec3 Component::getLocalPosition() {
    return this->localTransform.getPosition();
}

glm::quat Component::getLocalRotation() {
    return this->localTransform.getRotation();
}

glm::mat4 Component::getLocalMatrix() {
    return this->localTransform.getMatrix();
}

glm::mat4 Component::getWorldMatrix() {
    if (parentComponent) {
        return parentComponent->getWorldMatrix() * getLocalMatrix();
    }
    return getLocalMatrix();
}

Transform Component::getLocalTransform() const {
    return localTransform;
}

void Component::setLocalTransform(Transform transform) {
    this->localTransform = transform;
};

void Component::setWorldTransform(Transform transform) {
    this->worldTransform = transform;
};


void Component::setWorldPosition(glm::vec3 newPosition) {
    this->worldTransform.setPosition(newPosition);
}

void Component::setWorldScale(glm::vec3 newScale) {
    this->worldTransform.setScale(newScale);
}

void Component::setWorldRotation(glm::vec3 newRotation) {
    // convert degrees to quaternion
    this->worldTransform.setRotation(newRotation);
}

void Component::setWorldRotation(glm::quat rotation) {
    this->worldTransform.setRotation(rotation);
}

glm::vec3 Component::getWorldPosition() {
    return this->worldTransform.getPosition();
}


glm::quat Component::getWorldRotation() {
    return this->worldTransform.getRotation();
}

glm::mat4 Component::getTransformMatrix() {
    return this->worldTransform.getMatrix();
}

Transform Component::getWorldTransform() const {
    return worldTransform;
}

glm::vec3 Component::getLocalScale() {
    return this->localTransform.getScale();
}

bool Component::isDirty() const {
    return m_dirty;
}

void Component::setDirty(bool dirty) {
    Component::m_dirty = dirty;
}

bool Component::isReady() {
    return m_ready;
}

void Component::setReady(bool ready) {
    Component::m_ready = ready;
}

void Component::addChild(Component *child) {
    this->childComponents.push_back(child);
}

void Component::rotateX(float degrees) {
    this->localTransform.rotateX(degrees);
}

void Component::rotateY(float degrees) {
    this->localTransform.rotateY(degrees);
}

void Component::rotateZ(float degrees) {
    this->localTransform.rotateZ(degrees);
}

void Component::setLocalScale(float scale) {
    this->setLocalScale(glm::vec3(scale));
}

void Component::roll(float degrees) {
    this->localTransform.roll(degrees);
}

void Component::yaw(float degrees) {
    this->localTransform.yaw(degrees);
}

void Component::pitch(float degrees) {
    this->localTransform.pitch(degrees);
}

void Component::move(glm::vec3 offset) {
    localTransform.mPosition += offset;
}





