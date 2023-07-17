
#include "Camera.h"

Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch) :
        mPosition(pos), mWorldUp(up), mYaw(yaw), mPitch(pitch) {
    updateCameraVectors();
    updateProjectionMatrix();
    getViewMatrix();
}

glm::mat4 Camera::getViewMatrix() {
    if (mDirty) {
        mViewMatrix = glm::lookAt(mPosition, mPosition + mFront, mUp);
        mDirty = false;
    }
    return mViewMatrix;
}

void Camera::updateProjectionMatrix() {
    mProjectionMatrix = glm::perspective(glm::radians(mFOV), mAspectRatio, mNearClip, mFarClip);
}

glm::mat4 Camera::getProjectionMatrix() {
    return mProjectionMatrix;
}

[[maybe_unused]] void Camera::setAspectRatio(float aspectRatio) {
    this->mAspectRatio = aspectRatio;
    updateProjectionMatrix();
}

[[maybe_unused]] void Camera::setFOV(float fov) {
    this->mFOV = fov;
    updateProjectionMatrix();
}

[[maybe_unused]] void Camera::setClipPlanes(float nearClip, float farClip) {
    this->mNearClip = nearClip;
    this->mFarClip = farClip;
    updateProjectionMatrix();
}

void Camera::moveForward(float deltaTime) {
    mPosition += mFront * deltaTime;
    mDirty = true;
}

void Camera::moveBackward(float deltaTime) {
    mPosition -= mFront * deltaTime;
    mDirty = true;
}

void Camera::moveRight(float deltaTime) {
    mPosition += mRight * deltaTime;
    mDirty = true;
}

void Camera::moveLeft(float deltaTime) {
    mPosition -= mRight * deltaTime;
    mDirty = true;
}

void Camera::moveUp(float deltaTime) {
    mPosition += mUp * deltaTime;
    mDirty = true;
}

void Camera::moveDown(float deltaTime) {
    mPosition -= mUp * deltaTime;
    mDirty = true;
}


void Camera::rotate(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= 0.1f;
    yoffset *= 0.1f;

    mYaw += xoffset;
    mPitch += yoffset;

    if (constrainPitch) {
        if (mPitch > 89.0f) {
            mPitch = 89.0f;
        }
        if (mPitch < -89.0f) {
            mPitch = -89.0f;
        }
    }

    updateCameraVectors();
    mDirty = true;
}

void Camera::updateCameraVectors() {
    // Calculate the new m_front vector
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    newFront.y = sin(glm::radians(mPitch));
    newFront.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    mFront = glm::normalize(newFront);

    // Recalculate the m_right and m_up vectors
    mRight = glm::normalize(glm::cross(mFront, mWorldUp));
    mUp = glm::normalize(glm::cross(mRight, mFront));
}

glm::vec3 Camera::getLocalPosition() {
    return mPosition;
}

float Camera::getNearClip() const {
    return mNearClip;
}

float Camera::getFarClip() const {
    return mFarClip;
}
