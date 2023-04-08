#pragma once

#include "GraphicsAPI.h"

class API_OpenGL: public GraphicsAPI {

    void framebufferSizeCallback(GLFWwindow *window, int width, int height) override;

    unsigned int loadShader(std::string, std::string ) override;
    unsigned int compileShader(std::string &source, unsigned int type) override;

public:
    unsigned int setupMesh(Mesh *mesh) override;


private:
    void updateRendererConfig(RenderingConfig &) override;
    void renderMesh(Mesh *) override;

    unsigned int getFlag(GraphicsFlag flag);
};

