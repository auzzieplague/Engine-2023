#pragma once
#include <graphics/Texture.h>
#include <graphics/shader/ShaderProgram.h>
#include <graphics/RenderTarget.h>
#include <GPUInfo.h>
#include <cstdio>
#include <components/meshes/MeshData.h>
#include <components/meshes/Mesh.h>

class FrameBuffer;

class GraphicsBehaviour {

protected:
    GPUInfo *gpuInfo{};
    MeshData *fullScreenQuad;
    ShaderProgram *quadShader;
    RenderTarget * currentRenderTarget;
public:

    // buffer reference pool for cleanup
    std::vector<FrameBuffer *> frameBuffers;

    // Initialization
    bool initialised = false;

    virtual bool initialise() {return false;};
    virtual void queryCapabilities() {};
    virtual void displayCapabilities();

    virtual void compileShader(Shader *shader) {};
    virtual unsigned int linkShaderProgram(ShaderProgram *) {return 0;};
    virtual void useShaderProgram(ShaderProgram *) {};

    virtual unsigned int createFrameBuffer(FrameBuffer *fbo) {return 0;};
    virtual void resetFrameBuffer(FrameBuffer * buffer, int width, int height) {}
    virtual void setRenderTarget(RenderTarget * renderTarget) {this->currentRenderTarget = renderTarget;};
    virtual void renderTargetBind(RenderTarget *renderTarget){};
    virtual void resizeViewport(int width, int height, ...) {};

    virtual void createTexture(Texture *texture) {};
    virtual void bindTexture(Texture * texture) {};

    virtual  MeshData * allocateMeshData(MeshData *){return nullptr;};
    virtual MeshData* getSampleMeshData();
    MeshData *getFullScreenQuadMeshData();

    virtual void demoTriangle() {};

    virtual void renderTargetDrawMeshData(RenderTarget *renderTarget, std::vector<MeshData *> meshData){};
    virtual void renderTargetClearDepthBuffer(RenderTarget *renderTarget){};
    virtual void renderTargetClearColourBuffer(RenderTarget *renderTarget){};

    virtual void setProjectionMatrix(...) {};

    virtual void reportErrors(){};

    // can't call virtual functions from constructor so cleanup is just a level of abstraction
    ~GraphicsBehaviour() { this->cleanup();}
    void cleanup(){this->cleanupResources();};
    virtual void cleanupResources(){};
    virtual void shutdown(...) {};
};
