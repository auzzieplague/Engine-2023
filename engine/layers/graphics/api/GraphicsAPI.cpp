#pragma once

#include "GraphicsAPI.h"
#include "../../engine/components/meshes/Mesh.h" /// forward declaration override

unsigned int GraphicsAPI::compileShader(std::string &source, unsigned int type) {
    Debug::show("missing override for compileShader");
    return 0;
}

unsigned int GraphicsAPI::loadShader(std::string, std::string) {
    Debug::show("missing override for loadShader");
    return 0;
}

unsigned int GraphicsAPI::setupMesh(Mesh *instance) {
    Debug::show("missing override for setupMesh");
    return 0;
}

void GraphicsAPI::renderMesh(Mesh *) {
    Debug::show("missing override for renderMesh");
}

void GraphicsAPI::updateRendererConfig(RenderingConfig &) {
    Debug::show("missing override for updateRenderConfig");
}

void GraphicsAPI::framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    Debug::show("missing override for framebufferCallback");
}

unsigned int GraphicsAPI::getFlag(GraphicsFlag flag) {
    return 0;
}


