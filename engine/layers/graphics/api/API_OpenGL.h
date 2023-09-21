#pragma once

#include "GraphicsAPI.h"

class API_OpenGL : public GraphicsAPI {
public:

    int transformBufferSize = 1000;
    unsigned int transformBuffer = 0;
    unsigned int transformBufferBindingPoint = 0;

    void initialise() override;

     void setCapabilities() override;

    /* todo add a hook and replace glGetUniformLocation, with a map to cache the calls - then tests performance
     * modern OpenGL implementations have optimisations that can reduce the overhead of calling glGetUniformLocation,
     * so the performance difference between the two approaches may not be significant in practice.
    */
    void framebufferSizeCallback(GLFWwindow *window, int width, int height) override;

    RenderingConfig loadShader(std::string, std::string) override;

    unsigned int loadTexture (std::string) override;

    unsigned int compileShader(std::string &source, unsigned int type) override;

    void initialiseShader(RenderingConfig &) override;

    void beginRender(RenderingConfig &) override;

    void endRender(RenderingConfig &) override;

    unsigned int setupMesh(Mesh *mesh) override;

    unsigned int setupTerrain(HeightMap *heightmap) override;

    void renderMesh(Mesh *) override;
    void renderInstancedMesh(Mesh *, std::vector<glm::mat4> transforms) override;

    void readColourBufferRBGA(unsigned char *data, float x, float y, float width , float height) override;

    void readDepthBuffer(float *data, float x, float y, float width , float height) override;

    void flushBuffers() override;

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

    void shaderSetTransformList(const std::vector<glm::mat4> &mats) const override;

    void shaderSetView(const glm::mat4 &mat) const override;

    void shaderSetProjection(const glm::mat4 &mat) const override;

    void  shaderSetCamera(Camera *pCamera)  override;

};

