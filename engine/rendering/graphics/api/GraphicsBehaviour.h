#pragma once
#include <graphics/Texture.h>
#include <graphics/shader/ShaderProgram.h>
#include <graphics/RenderTarget.h>
#include <GPUInfo.h>
#include <cstdio>
#include <components/meshes/MeshData.h>

class VertexBuffer;
class IndexBuffer;
class FrameBuffer;
class BufferObject;
class GPULayout;

class GraphicsBehaviour {

protected:
    GPUInfo *gpuInfo{};
    MeshData *fullScreenQuad;
    ShaderProgram *quadShader;
    int currentTime=1;
public:

    // buffer reference pool for cleanup
    std::vector<BufferObject *> bufferObjects;
    std::vector<IndexBuffer *> indexBuffers;
    std::vector<VertexBuffer *> vertexBuffers;
    std::vector<FrameBuffer *> frameBuffers;
    std::vector<GPULayout *> gpuLayouts;

    // Initialization
    bool initialised = false;
    virtual bool initialise(...) { return false; };
    virtual void queryCapabilities(...) {  };
    virtual void displayCapabilities(...);

    /**
     * note we're passing preconfigured objects to the  api methods
     * these methods will initialise, transform , populate items on the graphics card
     * and store variables on the objects we passed for later reference
     *
     * some of these methods will be called from inside an instance of an object and they will
     * be passing through their own pointer (this)
     *
     * for example we wont be calling useShaderProgram from the engine,
     * shader->use() will call useShaderProgram(this)
     */

    // Resource Management
    virtual unsigned int createVertexBuffer(VertexBuffer* vb) {return 0;};
    virtual unsigned int createIndexBuffer(IndexBuffer *ib) {return 0;};
    virtual unsigned int createBufferObject(BufferObject *bo) {return 0;}; // VAO in opengl
    virtual unsigned int createFrameBuffer(FrameBuffer *fbo) {return 0;};

    virtual void compileShader(Shader *shader) {};
    virtual unsigned int linkShaderProgram(ShaderProgram *) {return 0;};
    virtual void useShaderProgram(ShaderProgram *) {};
    virtual void applyLayout(GPULayout *layout){};

    // Framebuffer and Render Target Management
    virtual void createTexture(Texture *texture) {};
    virtual void bindTexture(Texture * texture) {};
    virtual void setRenderTarget(RenderTarget * renderTarget) {};


    virtual void reportErrors(){};
    virtual void finalRender(RenderTarget *renderTarget){};
    virtual void renderTargetBind(RenderTarget *renderTarget){};
    virtual void renderTargetDrawMeshData(RenderTarget *renderTarget, std::vector<MeshData *> meshData){};
    virtual void renderTargetClearDepthBuffer(RenderTarget *renderTarget){};
    virtual void renderTargetClearColourBuffer(RenderTarget *renderTarget){};
    virtual  MeshData * allocateMeshData(MeshData *){return nullptr;};
    // Rendering
    virtual void bindVertexBuffer(VertexBuffer* vb) {};
    virtual void bindIndexBuffer(IndexBuffer* ib) {};
    virtual void bindBufferObject(BufferObject *bo) {}; // VAO in opengl

    virtual void drawIndexed(...) {};
    virtual void setUniforms(...) {};


    // Viewport and Projection
    virtual void setViewport(...) {};
    virtual void setProjectionMatrix(...) {};
    virtual void resizeViewport(...) {};

    // Shader Management
    virtual void compileShader(...) {};
    virtual void linkProgram(...) {};

    // Cleanup and Shutdown
    virtual void shutdown(...) {};
    virtual void demoTriangle(...) {};

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
