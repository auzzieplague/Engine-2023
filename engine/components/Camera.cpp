
#include "Camera.h"

Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch) :
        position(pos), worldUp(up), yaw(yaw), pitch(pitch), fov(45.0f), aspectRatio(1.0f), nearClip(0.1f),
        farClip(100.0f) {
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjectionMatrix() const {
    return glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
}

void Camera::setAspectRatio(float aspectRatio) {
    this->aspectRatio = aspectRatio;
}

void Camera::setFOV(float fov) {
    this->fov = fov;
}

void Camera::setClipPlanes(float nearClip, float farClip) {
    this->nearClip = nearClip;
    this->farClip = farClip;
}

void Camera::moveForward(float deltaTime) {
    position += front * deltaTime;
}

void Camera::moveBackward(float deltaTime) {
    position -= front * deltaTime;
}

void Camera::moveRight(float deltaTime) {
    position += right * deltaTime;
}

void Camera::moveLeft(float deltaTime) {
    position -= right * deltaTime;
}

void Camera::rotate(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= 0.1f;
    yoffset *= 0.1f;

    yaw += xoffset;
    pitch += yoffset;

    if (constrainPitch) {
        if (pitch > 89.0f) {
            pitch = 89.0f;
        }
        if (pitch < -89.0f) {
            pitch = -89.0f;
        }
    }

    updateCameraVectors();
}


void Camera::updateCameraVectors() {
    // Calculate the new front vector
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);

    // Recalculate the right and up vectors
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}