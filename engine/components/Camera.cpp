
#include "Camera.h"

Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch) :
        mPosition(pos), m_worldUp(up), m_yaw(yaw), m_pitch(pitch), m_fov(45.0f), m_aspectRatio(1.0f), m_nearClip(0.1f),
        m_farClip(100.0f) {
    updateCameraVectors();
    updateProjectionMatrix();
    getViewMatrix();
}

glm::mat4 Camera::getViewMatrix() {
    if (mDirty) {
        mViewMatrix = glm::lookAt(mPosition, mPosition + m_front, m_up);
        mDirty = false;
    }
    return mViewMatrix;
}

void Camera::updateProjectionMatrix() {
    mProjectionMatrix = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearClip, m_farClip);
}

glm::mat4 Camera::getProjectionMatrix() {
    return mProjectionMatrix;
}

[[maybe_unused]] void Camera::setAspectRatio(float aspectRatio) {
    this->m_aspectRatio = aspectRatio;
    updateProjectionMatrix();
}

[[maybe_unused]] void Camera::setFOV(float fov) {
    this->m_fov = fov;
    updateProjectionMatrix();
}

[[maybe_unused]] void Camera::setClipPlanes(float nearClip, float farClip) {
    this->m_nearClip = nearClip;
    this->m_farClip = farClip;
    updateProjectionMatrix();
}

void Camera::moveForward(float deltaTime) {
    mPosition += m_front * deltaTime;
    mDirty = true;
}

void Camera::moveBackward(float deltaTime) {
    mPosition -= m_front * deltaTime;
    mDirty = true;
}

void Camera::moveRight(float deltaTime) {
    mPosition += m_right * deltaTime;
    mDirty = true;
}

void Camera::moveLeft(float deltaTime) {
    mPosition -= m_right * deltaTime;
    mDirty = true;
}

void Camera::moveUp(float deltaTime) {
    mPosition += m_up * deltaTime;
    mDirty = true;
}

void Camera::moveDown(float deltaTime) {
    mPosition -= m_up * deltaTime;
    mDirty = true;
}


void Camera::rotate(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= 0.1f;
    yoffset *= 0.1f;

    m_yaw += xoffset;
    m_pitch += yoffset;

    if (constrainPitch) {
        if (m_pitch > 89.0f) {
            m_pitch = 89.0f;
        }
        if (m_pitch < -89.0f) {
            m_pitch = -89.0f;
        }
    }

    updateCameraVectors();
    mDirty = true;
}

void Camera::updateCameraVectors() {
    // Calculate the new m_front vector
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    newFront.y = sin(glm::radians(m_pitch));
    newFront.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(newFront);

    // Recalculate the m_right and m_up vectors
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}

glm::vec3 Camera::getLocalPosition() {
    return mPosition;
}
