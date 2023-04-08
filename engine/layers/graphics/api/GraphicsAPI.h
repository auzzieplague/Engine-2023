#pragma once

#include "../../GraphicsLayer.h"
#include "../../../AssetManager.h"
#include "RenderingConfig.h"

class Mesh;

class GraphicsAPI {

protected:
    static unsigned int shaderProgram;

public:

    const std::map< GraphicsFlag, unsigned int> flagMappings;

    virtual unsigned int loadShader(std::string, std::string);

    virtual unsigned int compileShader(std::string &source, unsigned int type);

    virtual unsigned int setupMesh(Mesh *);

    virtual unsigned int createMaterial();

    virtual void renderMesh(Mesh *);

    virtual void updateRendererConfig(RenderingConfig &);

    virtual void framebufferSizeCallback(GLFWwindow *window, int width, int height);

    virtual unsigned int getFlag(GraphicsFlag flag);
};


