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
    /*
     * Transparency is a more complex issue than setting opacity on the material
     * alpha blending will need to be enabled for items with transparent materials
     * they will have to be drawn using the painters algorithm or similar to be use in conjunction with zbuffer.
     *
     * Transparency will probably need to be property on the component itself,
     * allowing sub meshes with transparent pieces to be moved into a later rendering cycle
     */
    // float transparency;
public:
    // Constructor with default values
    Material() {
        randomAmbientColor();
        this->m_diffuseColor = {0.8f, 0.8f, 0.8f};
        this->m_specularColor = {1.0f, 1.0f, 1.0f};
        this->m_shininess = {32.0f};
    };

    const glm::vec3 &getDiffuseColor() const;

    void setDiffuseColor(const glm::vec3 &mDiffuseColor);

    const glm::vec3 &getSpecularColor() const;

    void setSpecularColor(const glm::vec3 &mSpecularColor);

    float getShininess() const;

    void setShininess(float mShininess);

    void randomAmbientColor() {
        // Set m_up the random number generator
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(0.0f, 1.0f);

        // Generate a random ambient color
        m_ambientColor = glm::vec3(dis(gen), dis(gen), dis(gen));
    }

    const glm::vec3 &getAmbientColor() const;

    void setAmbientColor(const glm::vec3 &mAmbientColor);
};
