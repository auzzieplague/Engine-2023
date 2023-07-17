#pragma once

#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera : public Component {
private:

    glm::vec3 mFront;
    glm::vec3 mUp;
    glm::vec3 mRight;
    glm::vec3 mWorldUp;
    float mYaw;
    float mPitch;
    float mFOV = 45.0f;
    float mAspectRatio = 16.0f / 9.0f;
    float mNearClip = 1.0f;
    float mFarClip = 9000.0f;

public:
    float getNearClip() const;
    float getFarClip() const;

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
