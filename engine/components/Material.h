#pragma once

#include "Component.h"

class GraphicsAPI;
/**
 * @author Michael.Whinfrey
 */
class Material : public Component {
protected:
    static GraphicsAPI *m_api;
    // todo add a quality enum, to determine what level of shader to use
    // sort models to be rendered by shaderID before render

    glm::vec3 m_ambientColor;     // Ambient color of the material
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

    // probably just have the transparency shader at the end of the sort.

    uint m_texture_diffuse = 0;
    uint m_texture_normal = 0;
    // float transparency;
public:
    enum SHADER_TYPE {
        SHADER_BASE,
        SHADER_DIFFUSE,
        SHADER_NORMAL,
        SHADER_PBR,
    };

    // Constructor with default values
    Material() {
        this->m_ambientColor = {0.25f, 0.25f, 0.25f};
        this->m_specularColor = {1.0f, 1.0f, 1.0f};
        this->m_shininess = 32.0f;
    };

    void setDiffuseTexture(unsigned int ID);
    void setNormalTexture(unsigned int ID);
    unsigned int getDiffuseTexture();
    unsigned int getNormalTexture();

    SHADER_TYPE getShaderType ();

    const glm::vec3 &getDiffuseColor() const;

    void setDiffuseColor(const glm::vec3 &mDiffuseColor);

    const glm::vec3 &getSpecularColor() const;

    void setSpecularColor(const glm::vec3 &mSpecularColor);

    float getShininess() const;

    void setShininess(float mShininess);

    void randomAmbientColor();

    const glm::vec3 &getAmbientColor() const;

    void setAmbientColor(const glm::vec3 &mAmbientColor);

    static void setGraphicsAPI(GraphicsAPI *pApi);

    void loadFromAsset(std::string category, const std::string& materialName);
};

