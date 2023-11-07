#pragma once
#include <vector>
#include <string>
#include "Shader.h"

class ShaderProgram {
private:
    bool compiled = false;
    static GraphicsAPI *graphicsApi;
public:

    unsigned int programID;

    static void setGraphicsAPI(GraphicsAPI *api);
    std::vector<Shader *> shaders;

    ShaderProgram* compileAndLink();
    ShaderProgram* use();

    ShaderProgram* addShader(Shader * shader);



    // add shader
//    Shader();
//    ~Shader();
//
//    void loadFromSource(const std::string& vertexSource, const std::string& fragmentSource);
//    void bind();
//    void unbind();
//    void setUniformInt(const std::string& name, int value);
//    void setUniformFloat(const std::string& name, float value);
//    void setUniformMatrix4(const std::string& name, const glm::mat4& matrix);
//    void release();
};
