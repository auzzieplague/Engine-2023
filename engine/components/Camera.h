#pragma once

#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera : public Component {
private:

    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldUp;
    float m_yaw;
    float m_pitch;
    float m_fov;
    float m_aspectRatio;
    float m_nearClip;
    float m_farClip;

    void updateCameraVectors();

public:
    glm::mat4 mViewMatrix;
    glm::mat4 mProjectionMatrix;
    glm::vec3 mPosition;

    explicit Camera(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f,
                    float pitch = 0.0f);

    glm::mat4 getViewMatrix();

    glm::mat4 getProjectionMatrix();

    void updateProjectionMatrix();

    [[maybe_unused]] void setAspectRatio(float aspectRatio);

    [[maybe_unused]] void setFOV(float fov);

    [[maybe_unused]] void setClipPlanes(float nearClip, float farClip);

    void moveForward(float deltaTime);

    void moveBackward(float deltaTime);

    void moveRight(float deltaTime);

    void moveLeft(float deltaTime);

    void moveUp(float deltaTime);

    void moveDown(float deltaTime);

    void rotate(float xoffset, float yoffset, bool constrainPitch = true);

    glm::vec3 getLocalPosition ();
};
