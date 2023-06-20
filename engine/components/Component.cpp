#include "Component.h"

void Component::setLocalPosition(glm::vec3 newPosition) {
    this->localTransform.setPosition(newPosition);
    updateFinalTransform();
}

void Component::setLocalRotation(glm::vec3 newRotation) {
    this->localTransform.setRotation(newRotation);
    updateFinalTransform();
}

void Component::rotate(glm::vec3 newRotation) {
    this->localTransform.rotate(newRotation);
    updateFinalTransform();
}

void Component::setLocalScale(glm::vec3 newScale) {
    this->localTransform.setScale(newScale);
    updateFinalTransform();
}

void Component::setLocalRotation(glm::quat rotation) {
    this->localTransform.setRotation(rotation);
    updateFinalTransform();
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
        child->worldTransform = this->finalTransform;
        child->updateFinalTransform();
    }
}

/**
 * updates combined transform of this component
 */
void Component::updateFinalTransform() {

    finalTransform.setFromMatrix(worldTransform.getMatrix() * localTransform.getMatrix());

//    glm::mat4 preTransform = this->worldTransform.getMatrix() * this->localTransform.getMatrix();
//    this->finalTransform.setPosition(glm::vec3(preTransform[3]));
//    this->finalTransform.setRotation(glm::quat_cast(preTransform));
    // todo - fix scale
//    this->finalTransform.setScale(this->worldTransform.getScale()*this->getLocalScale());
    this->updateChildTransforms();
}

void Component::setWorldPosition(glm::vec3 newPosition) {
    this->worldTransform.setPosition(newPosition);
    this->updateFinalTransform();
}

void Component::setWorldScale(glm::vec3 newScale) {
    this->worldTransform.setScale(newScale);
    this->updateFinalTransform();
}

void Component::setWorldRotation(glm::vec3 newRotation) {
    // convert degrees to quaternion
    this->worldTransform.setRotation(newRotation);
    this->updateFinalTransform();
}

void Component::setWorldRotation(glm::quat rotation) {
    this->worldTransform.setRotation(rotation);
    this->updateFinalTransform();
}

glm::vec3 Component::getWorldPosition() {
    return this->worldTransform.getPosition();
}


glm::quat Component::getWorldRotation() {
    return this->worldTransform.getRotation();
}

glm::mat4 Component::getTransformMatrix() {
    return this->finalTransform.getMatrix();
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
    updateFinalTransform();
}

void Component::rotateY(float degrees) {
    this->localTransform.rotateY(degrees);
    updateFinalTransform();
}

void Component::rotateZ(float degrees) {
    this->localTransform.rotateZ(degrees);
    updateFinalTransform();
}

void Component::setLocalScale(float scale) {
    this->setLocalScale(glm::vec3(scale));
}

Transform Component::getFinalTransform() {
    return this->finalTransform;
}

void Component::roll(float degrees) {
    this->localTransform.roll(degrees);
    updateFinalTransform();
}

void Component::yaw(float degrees) {
    this->localTransform.yaw(degrees);
    updateFinalTransform();
}

void Component::pitch(float degrees) {
    this->localTransform.pitch(degrees);
    updateFinalTransform();
}





