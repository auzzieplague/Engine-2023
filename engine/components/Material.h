#pragma once

#include "Component.h"

/**
 * @author Michael.Whinfrey
 */
class Material : public Component {
public:
    // Constructor with default values
    Material() {
       randomAmbientColor();
        this->diffuseColor = {0.8f, 0.8f, 0.8f};
        this->specularColor = {1.0f, 1.0f, 1.0f};
        this->shininess = {32.0f};
    };

    void randomAmbientColor() {
        // Set up the random number generator
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(0.0f, 1.0f);

        // Generate a random ambient color
        ambientColor = glm::vec3(dis(gen), dis(gen), dis(gen));
    }

    // Ambient color getter and setter
    glm::vec3 getAmbientColor() const { return ambientColor; }

    void setAmbientColor(const glm::vec3 &color) { ambientColor = color; }

    // Diffuse color getter and setter
    glm::vec3 getDiffuseColor() const { return diffuseColor; }

    void setDiffuseColor(const glm::vec3 &color) { diffuseColor = color; }

    // Specular color getter and setter
    glm::vec3 getSpecularColor() const { return specularColor; }

    void setSpecularColor(const glm::vec3 &color) { specularColor = color; }

    // Shininess getter and setter
    float getShininess() const { return shininess; }

    void setShininess(float value) { shininess = value; }

private:
    glm::vec3 ambientColor;     // Ambient color of the material
    glm::vec3 diffuseColor;     // Diffuse color of the material
    glm::vec3 specularColor;    // Specular color of the material
    float shininess;            // Shininess of the material
};

