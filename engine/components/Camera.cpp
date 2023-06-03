
#include "Camera.h"

Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch) :
        m_position(pos), m_worldUp(up), m_yaw(yaw), m_pitch(pitch), m_fov(45.0f), m_aspectRatio(1.0f), m_nearClip(0.1f),
        m_farClip(100.0f) {
    updateCameraVectors();
    updateProjectionMatrix();
    getViewMatrix();
}

glm::mat4 Camera::getViewMatrix() {
    if (m_dirty) {
        m_viewMatrix = glm::lookAt(m_position, m_position + m_front, m_up);
        m_dirty = false;
    }
    return m_viewMatrix;
}

void Camera::updateProjectionMatrix() {
    m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearClip, m_farClip);
}

glm::mat4 Camera::getProjectionMatrix() {
    return m_projectionMatrix;
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
    m_position += m_front * deltaTime;
    m_dirty = true;
}

void Camera::moveBackward(float deltaTime) {
    m_position -= m_front * deltaTime;
    m_dirty = true;
}

void Camera::moveRight(float deltaTime) {
    m_position += m_right * deltaTime;
    m_dirty = true;
}

void Camera::moveLeft(float deltaTime) {
    m_position -= m_right * deltaTime;
    m_dirty = true;
}

void Camera::moveUp(float deltaTime) {
    m_position += m_up * deltaTime;
    m_dirty = true;
}

void Camera::moveDown(float deltaTime) {
    m_position -= m_up * deltaTime;
    m_dirty = true;
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
    m_dirty = true;
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

glm::vec3 Camera::getPosition() {
    return m_position;
}
