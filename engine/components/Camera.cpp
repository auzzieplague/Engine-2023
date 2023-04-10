
#include "Camera.h"

Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch) :
        position(pos), worldUp(up), yaw(yaw), pitch(pitch), fov(45.0f), aspectRatio(1.0f), nearClip(0.1f),
        farClip(100.0f) {
    updateCameraVectors();
    updateProjectionMatrix();
    getViewMatrix();
}

glm::mat4 Camera::getViewMatrix() {
    if (isDirty) {
        viewMatrix =  glm::lookAt(position, position + front, up);
        isDirty = false;
    }
    return viewMatrix;
}

void Camera::updateProjectionMatrix()  {
    projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
}

glm::mat4 Camera::getProjectionMatrix()  {
    return projectionMatrix;
}

void Camera::setAspectRatio(float aspectRatio) {
    this->aspectRatio = aspectRatio;
    updateProjectionMatrix();
}

void Camera::setFOV(float fov) {
    this->fov = fov;
    updateProjectionMatrix();
}

void Camera::setClipPlanes(float nearClip, float farClip) {
    this->nearClip = nearClip;
    this->farClip = farClip;
    updateProjectionMatrix();
}

void Camera::moveForward(float deltaTime) {
    position += front * deltaTime;
    isDirty= true;
}

void Camera::moveBackward(float deltaTime) {
    position -= front * deltaTime;
    isDirty= true;
}

void Camera::moveRight(float deltaTime) {
    position += right * deltaTime;
    isDirty= true;
}

void Camera::moveLeft(float deltaTime) {
    position -= right * deltaTime;
    isDirty= true;
}

void Camera::moveUp(float deltaTime) {
    position += up * deltaTime;
    isDirty= true;
}

void Camera::moveDown(float deltaTime) {
    position -= up * deltaTime;
    isDirty= true;
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
    isDirty = true;
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
