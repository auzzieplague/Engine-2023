#pragma once

#include "GraphicsAPI.h"

class API_DirectX : public GraphicsAPI {
    void framebufferSizeCallback(GLFWwindow *window, int width, int height) override;

    unsigned int loadShader(std::string, std::string) override;

    unsigned int compileShader(std::string &source, unsigned int type) override;

    void beginRender(RenderingConfig &) override;

    unsigned int setupMesh(MeshData *mesh) override;

    void renderMesh(MeshData *) override;

    unsigned int getFlag(GraphicsFlag flag) override;
};


