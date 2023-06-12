#pragma once

#include "GraphicsAPI.h"

class API_OpenGL : public GraphicsAPI {
public:
    RenderingConfig *currentRenderingConfig;

    /* todo add a hook and replace glGetUniformLocation, with a map to cache the calls - then tests performance
     * modern OpenGL implementations have optimisations that can reduce the overhead of calling glGetUniformLocation,
     * so the performance difference between the two approaches may not be significant in practice.
    */
    void framebufferSizeCallback(GLFWwindow *window, int width, int height) override;

    unsigned int loadShader(std::string, std::string) override;

    unsigned int loadTexture (std::string) override;

    unsigned int compileShader(std::string &source, unsigned int type) override;

    void updateRendererConfig(RenderingConfig &) override;

    unsigned int setupMesh(Mesh *mesh) override;

    unsigned int setupTerrain(HeightMap *heightmap) override;

    void renderMesh(Mesh *) override;

    void renderTerrain(Terrain *terrain) override;

    unsigned int getFlag(GraphicsFlag flag) override;

    void shaderSetVec4(const std::string &name, const glm::vec4 &value) const override;

    void shaderSetBool(const std::string &name, bool value) const override;

    void shaderSetInt(const std::string &name, int value) const override;

    void shaderSetVec2(const std::string &name, const glm::vec2 &value) const override;

    void shaderSetVec3(const std::string &name, const glm::vec3 &value) const override;

    void shaderSetMat2(const std::string &name, const glm::mat2 &mat) const override;

    void shaderSetMat3(const std::string &name, const glm::mat3 &mat) const override;

    void shaderSetMat4(const std::string &name, const glm::mat4 &mat) const override;

    void shaderSetFloat(const std::string &name, float value) const override;

    void shaderSetMaterial(Material material) const override;

    void shaderSetTransform(const glm::mat4 &mat) const override;

    void shaderSetView(const glm::mat4 &mat) const override;

    void shaderSetProjection(const glm::mat4 &mat) const override;

    void  shaderSetCamera(Camera *pCamera)  override;

};

