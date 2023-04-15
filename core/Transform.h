#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform {
public:
    Transform();
    [[nodiscard]] glm::vec3 getPosition() const;
    [[nodiscard]] glm::quat getRotation() const;
    [[nodiscard]] glm::vec3 getScale() const;
    [[nodiscard]] glm::mat4 getModelMatrix() const;
    void setPosition(glm::vec3 position);
    void setRotation(glm::quat rotation);
    void setScale(glm::vec3 scale);
    void translate(glm::vec3 translation);
    void rotate(glm::vec3 axis, float angle);
    void scale(glm::vec3 scaleFactor);
private:
    glm::vec3 m_position;
    glm::quat m_rotation;
    glm::vec3 m_scale;
};