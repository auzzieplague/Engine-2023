#pragma once

#include "GraphicsAPI.h"
#include "../../engine/components/meshes/Mesh.h" /// forward declaration override

unsigned int GraphicsAPI::compileShader(std::string &source, unsigned int type) {
    Debug::show("missing override for compileShader");
    return 0;
}

RenderingConfig GraphicsAPI::loadShader(std::string, std::string) {
    Debug::show("missing override for loadShader");
    return RenderingConfig();
}

unsigned int GraphicsAPI::setupMesh(Mesh *instance) {
    Debug::show("missing override for setupMesh");
    return 0;
}

void GraphicsAPI::renderMesh(Mesh *) {
    Debug::show("missing override for renderMesh");
}


void GraphicsAPI::renderInstancedMesh(Mesh *, std::vector<glm::mat4> transforms){
    Debug::show("missing override for renderInstancedMesh ");
}

void GraphicsAPI::beginRender(RenderingConfig &) {
    Debug::show("missing override for beginRender");
}

void GraphicsAPI::endRender(RenderingConfig &) {
    Debug::show("missing override for endRender");
}


void GraphicsAPI::framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    Debug::show("missing override for framebufferCallback");
}

unsigned int GraphicsAPI::getFlag(GraphicsFlag flag) {
    return 0;
}

unsigned int GraphicsAPI::setupTerrain(HeightMap * heightMap) {
    Debug::show("missing override for setupTerrain");
    return 0;
}

unsigned int GraphicsAPI::loadTexture(std::string filename) {
    Debug::show("missing override for loadTexture");
    return 0;
}

void GraphicsAPI::readColourBufferRBGA(unsigned char *data, float x, float y, float width , float height) {
    Debug::show("missing override for readColourBufferRBGA");
}

void GraphicsAPI::readDepthBuffer(float *data, float x, float y, float width , float height) {
    Debug::show("missing override for readDepthBuffer");
}

void GraphicsAPI::flushBuffers() {
    Debug::show("missing override for flushBuffers");
}

void GraphicsAPI::setCapabilities() {
    Debug::show("missing override for setCapabilities");
}

void GraphicsAPI::initialiseShader(RenderingConfig &) {
    Debug::show("missing override for initialiseShader");
}

void GraphicsAPI::displayCapabilities() {
    std::cout << " - Graphics Card: " << capabilities.gpuName << std::endl;
    std::cout << " - Max Texture Units: " << capabilities.maxTextureUnits << std::endl;
    std::cout << " - Max Resolution: " << capabilities.maxResolutionX << "x" << capabilities.maxResolutionY << std::endl;
    std::cout << " - Max Anisotropy: " << capabilities.maxAnisotropy << "x" << std::endl;
    std::cout << " - Max Render Targets: " << capabilities.maxRenderTargets << std::endl;
    std::cout << " - Max Uniform Buffer Bindings: " << capabilities.maxUniformBufferBindings << std::endl;
}

void GraphicsAPI::initialise() {
    Debug::show("missing override for initialise");
}

