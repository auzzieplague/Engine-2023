#include "Component.h"

void Component::setPosition(glm::vec3 newPosition) {
    this->localTransform.setPosition(newPosition);
    onTransformChange();
}

void Component::setLocalRotation(glm::vec3 newRotation) {
    this->localTransform.setRotation(newRotation);
    onTransformChange();
}

void Component::rotate(glm::vec3 newRotation) {
    this->localTransform.rotate(newRotation);
    onTransformChange();
}

void Component::scale(float scale) {
    this->scale(glm::vec3(scale));
}

void Component::scale(glm::vec3 scale) {
    this->localTransform.scale(scale);
    onTransformChange();
}

void Component::setLocalScale(glm::vec3 newScale) {
    this->localTransform.setScale(newScale);
    onTransformChange();
}

void Component::setLocalRotation(glm::quat rotation) {
    this->localTransform.setRotation(rotation);
    onTransformChange();
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

void Component::setLocalTransform(Transform transform) {
    this->localTransform = transform;
    onTransformChange();
};

Transform Component::getWorldTransform() const {
    return worldTransform;
}

glm::vec3 Component::getLocalScale() {
    return this->localTransform.getScale();
}

bool Component::isDirty() const {
    return mDirty;
}

void Component::setDirty(bool dirty) {
    Component::mDirty = dirty;
}

bool Component::isReady() {
    return mReady;
}

void Component::setReady(bool ready) {
    Component::mReady = ready;
}

void Component::addChild(Component *child) {
    this->childComponents.push_back(child);
}

void Component::rotateX(float degrees) {
    this->localTransform.rotateX(degrees);
    onTransformChange();
}

void Component::rotateY(float degrees) {
    this->localTransform.rotateY(degrees);
    onTransformChange();
}

void Component::rotateZ(float degrees) {
    this->localTransform.rotateZ(degrees);
    onTransformChange();
}

void Component::setLocalScale(float scale) {
    this->setLocalScale(glm::vec3(scale));
    onTransformChange();
}

void Component::roll(float degrees) {
    this->localTransform.roll(degrees);
    onTransformChange();
}

void Component::yaw(float degrees) {
    this->localTransform.yaw(degrees);
    onTransformChange();
}

void Component::pitch(float degrees) {
    this->localTransform.pitch(degrees);
    onTransformChange();
}

void Component::move(glm::vec3 offset) {
    localTransform.mPosition += offset;
    onTransformChange();
}

void Component::setFilePath(const std::string &fullPath) {
    size_t separatorPos = fullPath.find_last_of("/\\");
    if (separatorPos != std::string::npos) {
        filePath = fullPath.substr(0, separatorPos + 1);
        fileName = fullPath.substr(separatorPos + 1);
    } else {
        filePath = "";
        fileName = fullPath;
    }

    // set Name
     separatorPos = fileName.find_last_of(".");
     this->objectName = fileName.substr(0, separatorPos);
}

const std::string &Component::getFilePath() const {
    return filePath;
}

const std::string &Component::getFileName() const {
    return fileName;
}

void Component::autoScale() {
    Debug::show("Auto scale not supported for component "+this->getIdentifier());
}

void Component::setSelectable(bool selectable) {
    this->selectable = selectable;
}





