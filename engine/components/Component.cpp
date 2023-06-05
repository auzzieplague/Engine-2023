#include "Component.h"

void Component::setPosition(glm::vec3 newPosition) {
//    this->m_transform.setPosition(newPosition);
    glm::vec3 deltaPosition = newPosition - m_transform.getPosition();
    m_transform.setPosition(newPosition);

    // Update the world transform for this component
//    worldTransform = m_transform;

    // Transform the child components relative to the new position
    for (Component* child : childComponents) {
        glm::vec3 childPosition = child->getTransform().getPosition();
        glm::vec3 transformedPosition = childPosition + deltaPosition;
        child->setPosition(transformedPosition);
    }
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


