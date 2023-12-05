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
    int currentTime=1;
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

    virtual void createTexture(Texture *texture) {};
    virtual void bindTexture(Texture * texture) {};


    virtual void reportErrors(){};
    virtual void renderTargetBind(RenderTarget *renderTarget){};
    virtual void renderTargetDrawMeshData(RenderTarget *renderTarget, std::vector<MeshData *> meshData){};
    virtual void renderTargetClearDepthBuffer(RenderTarget *renderTarget){};
    virtual void renderTargetClearColourBuffer(RenderTarget *renderTarget){};
    virtual  MeshData * allocateMeshData(MeshData *){return nullptr;};
    // Rendering
    virtual void drawIndexed(...) {};
    virtual void setUniforms(...) {};


    // Viewport and Projection
    virtual void setViewport(...) {};
    virtual void setProjectionMatrix(...) {};
    virtual void resizeViewport(int width, int height, ...) {};

    // Shader Management
    virtual void compileShader(...) {};
    virtual void linkProgram(...) {};

    // Cleanup and Shutdown
    virtual void shutdown(...) {};
    virtual void demoTriangle() {};

    virtual unsigned int getFlagCode(const char *string);

    virtual MeshData* getSampleMeshData();

    virtual void cleanupResources(){};

    ~GraphicsBehaviour() {
        this->cleanup();
    }

    void cleanup(){
        this->cleanupResources();
    };

    MeshData *getFullScreenQuadMeshData();


};
