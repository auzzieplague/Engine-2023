#include "ShaderProgram.h"
#include <GraphicsAPI.h> // override forward declaration of graphics api here


GraphicsAPI *ShaderProgram::graphicsApi;

void ShaderProgram::setGraphicsAPI(GraphicsAPI *api) {
    ShaderProgram::graphicsApi = api;
}

ShaderProgram *ShaderProgram::compileAndLink() {
    ShaderProgram::graphicsApi->linkShaderProgram(this);
    return this;
}

ShaderProgram *ShaderProgram::use() {
    ShaderProgram::graphicsApi->useShaderProgram(this);
    return this;
}

ShaderProgram *ShaderProgram::addShader(Shader *shader) {
    this->shaders.push_back(shader);
    return this;
}
