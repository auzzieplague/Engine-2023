#include "Component.h"

void Component::setLocalPosition(glm::vec3 newPosition) {
    this->localTransform.setPosition(newPosition);
    updateCombinedTransform();
}

void Component::setLocalRotation(glm::vec3 newRotation) {
    this->localTransform.setRotation(newRotation);
    updateCombinedTransform();
}

void Component::setLocalScale(glm::vec3 newScale) {
    this->localTransform.setScale(newScale);
    updateCombinedTransform();
}

void Component::setLocalRotation(glm::quat rotation) {
    this->localTransform.setRotation(rotation);
    updateCombinedTransform();
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

Transform Component::getLocalTransform() const {
    return localTransform;
}

void Component::setLocalTransform(Transform transform) {
    this->localTransform = transform;
};

void Component::setWorldTransform(Transform transform) {
    this->worldTransform = transform;
};

void Component::updateChildTransforms() {
    for (auto child: this->childComponents) {
        // update world position of child to reflect parent position changes
        child->worldTransform = this->combinedTransform;
        child->updateCombinedTransform();
    }
}

/**
 * updates combined transform of this component
 */
void Component::updateCombinedTransform() {
    glm::mat4 preTransform = this->worldTransform.getMatrix() * this->localTransform.getMatrix();
    this->combinedTransform.setPosition(glm::vec3(preTransform[3]));
    this->combinedTransform.setRotation(glm::quat_cast(preTransform));
//    this->combinedTransform.setScale(this->worldTransform.getScale()*this->getLocalScale());
    this->updateChildTransforms();
}

void Component::setWorldPosition(glm::vec3 newPosition) {
    this->worldTransform.setPosition(newPosition);
    this->updateCombinedTransform();
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
    return this->combinedTransform.getMatrix();
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
    updateCombinedTransform();
}

void Component::rotateY(float degrees) {
    this->localTransform.rotateY(degrees);
    updateCombinedTransform();
}

void Component::rotateZ(float degrees) {
    this->localTransform.rotateZ(degrees);
    updateCombinedTransform();
}




