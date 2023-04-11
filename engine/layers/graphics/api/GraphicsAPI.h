#pragma once

#include "../../GraphicsLayer.h"
#include "../../../AssetManager.h"
#include "RenderingConfig.h"

class Mesh;

class GraphicsAPI {

protected:

public:

    virtual unsigned int loadShader(std::string, std::string);

    virtual unsigned int compileShader(std::string &source, unsigned int type);

    virtual unsigned int setupMesh(Mesh *);

    virtual void renderMesh(Mesh *);

    virtual void updateRendererConfig(RenderingConfig &);

    virtual void framebufferSizeCallback(GLFWwindow *window, int width, int height);

    virtual unsigned int getFlag(GraphicsFlag flag);

    virtual void shaderSetBool(const std::string& name, bool value) const {};
    virtual void shaderSetInt(const std::string& name, int value) const {};
    virtual void shaderSetFloat(const std::string& name, float value) const {};
    virtual void shaderSetVec2(const std::string& name, const glm::vec2& value) const {};
    virtual void shaderSetVec3(const std::string& name, const glm::vec3& value) const {};
    virtual void shaderSetVec4(const std::string& name, const glm::vec4& value) const {};
    virtual void shaderSetMat2(const std::string& name, const glm::mat2& mat) const {};
    virtual void shaderSetMat3(const std::string& name, const glm::mat3& mat) const {};
    virtual void shaderSetMat4(const std::string& name, const glm::mat4& mat) const {};

    virtual void shaderSetMaterial(Material material) const {};
    virtual void shaderSetTransform(const glm::mat4& mat) const {};
    virtual void shaderSetView(const glm::mat4& mat) const {};
    virtual void shaderSetProjection(const glm::mat4& mat) const {};
};


