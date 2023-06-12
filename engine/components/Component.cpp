#include "Component.h"

void Component::setLocalPosition(glm::vec3 newPosition) {
    this->localTransform.setPosition(newPosition);
    // update world transform
}

void Component::setLocalRotation(glm::vec3 newRotation) {
    // convert degrees to quaternion
    this->localTransform.setRotation(newRotation);
    updateCombinedTransform();
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
    for (auto child: this->childComponents){
        // update world position of child to reflect parent position changes
        child->worldTransform = this->combinedTransform;
        child->updateCombinedTransform();
        child->updateChildTransforms();
    }
}

/**
 * updates combined transform of this component
 */
void Component::updateCombinedTransform() {
    glm::mat4 preTransform = this->worldTransform.getMatrix() *this->localTransform.getMatrix();
    this->combinedTransform.setPosition(glm::vec3(preTransform[3]));
    this->combinedTransform.setRotation(glm::quat_cast(preTransform));
    this->updateChildTransforms();
}

void Component::setWorldPosition(glm::vec3 newPosition) {
    this->worldTransform.setPosition(newPosition);
    this->updateCombinedTransform();
    updateChildTransforms();
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



glm::vec3 Component::getScale() {
    return this->localTransform.getScale();
}

void Component::setScale(glm::vec3 newScale) {
    this->localTransform.setScale(newScale);
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

/**
 * rotate local position around a pivot point
 * @param pivotPoint
 * @param degrees
 */
void Component::rotateAround(glm::vec3 pivotPoint, glm::quat rotation) {
    // Calculate the rotation quaternions around each axis
//    glm::quat rotationX = glm::angleAxis(glm::radians(degrees.x), glm::vec3(1.0f, 0.0f, 0.0f));
//    glm::quat rotationY = glm::angleAxis(glm::radians(degrees.y), glm::vec3(0.0f, 1.0f, 0.0f));
//    glm::quat rotationZ = glm::angleAxis(glm::radians(degrees.z), glm::vec3(0.0f, 0.0f, 1.0f));
//
//    // Combine the rotation quaternions
//    glm::quat rotation = rotationZ * rotationY * rotationX;
//
//    // Rotate the component around the pivot point
    glm::vec3 position = localTransform.getPosition();
    glm::vec3 rotatedPosition = glm::rotate(rotation, position - pivotPoint) + pivotPoint;
    worldTransform.setPosition(rotatedPosition);
    worldTransform.setRotation(rotation * localTransform.getRotation());
//
//    // Update the world transform for this component
//    worldTransform = localTransform;
//
//    // Rotate the child components around the pivot point
//    for (Component *child: childComponents) {
//        glm::vec3 childPosition = child->getLocalTransform().getPosition();
//        glm::vec3 rotatedChildPosition = glm::rotate(rotation, childPosition - pivotPoint) + pivotPoint;
//        glm::vec3 childRotation = child->getLocalTransform().getRotationEuler();
//        childRotation += degrees;
//        child->setLocalPosition(rotatedChildPosition);
//        child->setLocalRotation(childRotation);
//        child->rotateAround(pivotPoint, degrees);
//    }
}

void Component::addChild(Component *child) {
    this->childComponents.push_back(child);
}



