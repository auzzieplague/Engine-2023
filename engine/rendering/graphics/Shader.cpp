
#include "Shader.h"
#include "GraphicsAPI.h"

GraphicsAPI *Shader::graphicsApi;

void Shader::setGraphicsAPI(GraphicsAPI *api) {
    Shader::graphicsApi = api;
}

Shader *Shader::loadFromSource(const std::string &sourceCode) {
    return this;
}

Shader *Shader::setSource(const std::string &sourceCode) {
    this->source = sourceCode;
    return this;
}

Shader::Shader(unsigned int type) : type(type) {}

Shader *Shader::compile() {
    Shader::graphicsApi->compileShader(this);
    this->compiled = true;
    return this;
}

Shader::Shader(unsigned int type, const std::string& fileName) {
    this->type = type;
    this->loadFromSource(fileName);
}
