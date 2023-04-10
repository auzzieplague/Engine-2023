#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera: public Component {
private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    float yaw;
    float pitch;
    float fov;
    float aspectRatio;
    float nearClip;
    float farClip;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    void updateCameraVectors();

public:
    explicit Camera(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);
     glm::mat4 getViewMatrix() ;
     glm::mat4 getProjectionMatrix() ;
    void updateProjectionMatrix();
    void setAspectRatio(float aspectRatio);
    void setFOV(float fov);
    void setClipPlanes(float nearClip, float farClip);
    void moveForward(float deltaTime);
    void moveBackward(float deltaTime);
    void moveRight(float deltaTime);
    void moveLeft(float deltaTime);
    void moveUp(float deltaTime);
    void moveDown(float deltaTime);
    void rotate(float xoffset, float yoffset, bool constrainPitch = true);
};
