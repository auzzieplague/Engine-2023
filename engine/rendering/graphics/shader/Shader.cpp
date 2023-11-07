
#include "Shader.h"
#include "GraphicsAPI.h"
#include "AssetLoader.h"

GraphicsAPI *Shader::graphicsApi;

void Shader::setGraphicsAPI(GraphicsAPI *api) {
    Shader::graphicsApi = api;
}

Shader *Shader::loadFromSource(const std::string &fileName) {
    //todo type Extension map .. will need to be an API method ... to allow different extensions and also _postfix's
    std::string ext = ".vert";
    if (this->type == FRAGMENT_SHADER) ext = ".frag";

    // items stored under their own folder e.g. general folder contains general.vert, general.frag
    this->source = AssetLoader::loadShaderFile(fileName+"/"+fileName+ext);
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
