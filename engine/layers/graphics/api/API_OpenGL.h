#pragma once

#include "GraphicsAPI.h"

class API_OpenGL: public GraphicsAPI {
public:
    RenderingConfig *currentRenderingConfig;
    void framebufferSizeCallback(GLFWwindow *window, int width, int height) override;

    unsigned int loadShader(std::string, std::string ) override;
    unsigned int compileShader(std::string &source, unsigned int type) override;

    void updateRendererConfig(RenderingConfig &) override;
    unsigned int setupMesh(Mesh *mesh) override;
    void renderMesh(Mesh *) override;

    unsigned int getFlag(GraphicsFlag flag) override;

//    void shaderSetVec4(const std::string& name, const glm::vec4& value) const override;

//    void shaderSetBool(const std::string& name, bool value) const override;
//    void shaderSetInt(const std::string& name, int value) const;
//    void shaderSetFloat(const std::string& name, float value) const;
//    void shaderSetVec2(const std::string& name, const glm::vec2& value) const;
//    void shaderSetVec3(const std::string& name, const glm::vec3& value) const;
//    void shaderSetMat2(const std::string& name, const glm::mat2& mat) const;
//    void shaderSetMat3(const std::string& name, const glm::mat3& mat) const;
    void shaderSetMat4(const std::string& name, const glm::mat4& mat) const;


};

