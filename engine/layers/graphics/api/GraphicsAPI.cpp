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

void GraphicsAPI::renderMesh(Mesh *, int) {
    Debug::show("missing override for renderMesh instanced");
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


