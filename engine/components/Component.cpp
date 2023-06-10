#include "Component.h"

void Component::setLocalPosition(glm::vec3 newPosition) {
    this->localTransform.setPosition(newPosition);
    // update world transform
}

void Component::setLocalRotation(glm::vec3 newRotation) {
    // convert degrees to quaternion
    this->localTransform.setRotation(newRotation);
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
    // children don't use their own world positions, they rely on the parent position plus their local offsets.
    for (auto child: this->childComponents){
        child->setWorldPosition(this->worldTransform.getPosition()+child->getLocalPosition());
//        child->rotateAround(this->worldTransform.getPosition(),this->localTransform.getRotation());
        child->setWorldRotation(this->localTransform.getRotation()+child->getLocalRotation()); // ? not really
        child->updateCombinedTransform();
    }
}

/**
 * updates world transform of this
 */
void Component::updateCombinedTransform() {
    this->combinedTransform.setPosition(this->worldTransform.getPosition()+this->localTransform.getPosition());
    this->combinedTransform.setRotation(this->worldTransform.getRotation()+this->localTransform.getRotation());
}




void Component::setWorldPosition(glm::vec3 newPosition) {
    this->worldTransform.setPosition(newPosition);
    this->updateCombinedTransform();
    this->updateChildTransforms();
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



