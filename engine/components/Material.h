#pragma once

#include "Component.h"

/**
 * @author Michael.Whinfrey
 */
class Material : public Component {
private:
    glm::vec3 m_ambientColor;     // Ambient color of the material
    glm::vec3 m_diffuseColor;     // Diffuse color of the material
    glm::vec3 m_specularColor;    // Specular color of the material
    float m_shininess;            // Shininess of the material
public:
    // Constructor with default values
    Material() {
       randomAmbientColor();
        this->m_diffuseColor = {0.8f, 0.8f, 0.8f};
        this->m_specularColor = {1.0f, 1.0f, 1.0f};
        this->m_shininess = {32.0f};
    };

    void randomAmbientColor() {
        // Set m_up the random number generator
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(0.0f, 1.0f);

        // Generate a random ambient color
        m_ambientColor = glm::vec3(dis(gen), dis(gen), dis(gen));
    }

    // Ambient color getter and setter
    glm::vec3 getAmbientColor() const { return m_ambientColor; }

    void setAmbientColor(const glm::vec3 &color) { m_ambientColor = color; }

    // Diffuse color getter and setter
    glm::vec3 getDiffuseColor() const { return m_diffuseColor; }

    void setDiffuseColor(const glm::vec3 &color) { m_diffuseColor = color; }

    // Specular color getter and setter
    glm::vec3 getSpecularColor() const { return m_specularColor; }

    void setSpecularColor(const glm::vec3 &color) { m_specularColor = color; }

    // Shininess getter and setter
    float getShininess() const { return m_shininess; }

    void setShininess(float value) { m_shininess = value; }


};

