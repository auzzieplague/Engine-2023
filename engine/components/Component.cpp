#include "Component.h"

void Component::setPosition(glm::vec3 newPosition) {
    this->transform.setPosition(newPosition);
}

void Component::setRotation(glm::vec3 newRotation) {
    this->transform.setRotation(newRotation);
}

void Component::setScale(glm::vec3 newScale) {
    this->transform.setScale(newScale);
}

glm::vec3 Component::getPosition() {
    return this->transform.getPosition();
}

glm::vec3 Component::getScale() {
    return this->transform.getScale();
}

glm::quat  Component::getRotation() {
    return this->transform.getRotation();
}

glm::mat4 Component::getModelMatrix() {
    return this->transform.getModelMatrix();
}

const Transform &Component::getTransform() const {
    return transform;
}

bool Component::isDirty() const {
    return dirty;
}

void Component::setDirty(bool dirty) {
    Component::dirty = dirty;
}

bool Component::isReady() {
    return ready;
}

void Component::setReady(bool ready) {
    Component::ready = ready;
}
