#include "ShaderProgram.h"
#include <GraphicsAPI.h> // override forward declaration of graphics api here


GraphicsAPI *ShaderProgram::graphicsApi;

void ShaderProgram::setGraphicsAPI(GraphicsAPI *api) {
    ShaderProgram::graphicsApi = api;
}

void ShaderProgram::compileAndLink() {
    ShaderProgram::graphicsApi->linkShaderProgram(this);
}

void ShaderProgram::use() {
    ShaderProgram::graphicsApi->useShaderProgram(this);
}
