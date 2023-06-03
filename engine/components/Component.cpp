#include "Component.h"

void Component::setPosition(glm::vec3 newPosition) {
    this->m_transform.setPosition(newPosition);
}

void Component::setRotation(glm::vec3 newRotation) {
    // convert degrees to quaternion
    this->m_transform.setRotation(newRotation);
}

void Component::setScale(glm::vec3 newScale) {
    this->m_transform.setScale(newScale);
}

glm::vec3 Component::getPosition() {
    return this->m_transform.getPosition();
}

glm::vec3 Component::getScale() {
    return this->m_transform.getScale();
}

glm::quat Component::getRotation() {
    return this->m_transform.getRotation();
}

glm::mat4 Component::getMatrix() {
    return this->m_transform.getMatrix();
}

Transform Component::getTransform() const {
    return m_transform;
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


