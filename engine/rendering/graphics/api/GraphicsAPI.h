#pragma once

#include <GraphicsBehaviour.h>

/*
* Implements Strategy pattern - behaviour must be assigned to api such as API_OpenGL behaviour
*/

class Mesh;

class GraphicsAPI {
    GraphicsBehaviour *api;
public:

    explicit GraphicsAPI(GraphicsBehaviour *api){
        this->api = api;
//        this->queryCapabilities();
    }

    void setBehaviour(GraphicsBehaviour *behavior) {
        this->api = behavior;
    }

    bool initialise() { return this->api->initialise(); };
    void queryCapabilities() { this->api->queryCapabilities(); };
    void displayCapabilities() { this->api->displayCapabilities(); };

    void compileShader(Shader *shader) { this->api->compileShader(shader); };
    unsigned int linkShaderProgram(ShaderProgram *program) { return this->api->linkShaderProgram(program); };
    void useShaderProgram(ShaderProgram *program) { this->api->useShaderProgram(program); };

    void createFrameBuffer(FrameBuffer *fbo) { this->api->createFrameBuffer(fbo); };
    void resetFrameBuffer(FrameBuffer * buffer, int width, int height) { return this->api->resetFrameBuffer(buffer, width, height);}
    void setRenderTarget(RenderTarget * renderTarget) { this->api->setRenderTarget(renderTarget); };
    void renderTargetBind(RenderTarget *renderTarget){ this->api->renderTargetBind(renderTarget);};

    void createTexture(Texture * texture) {return this->api->createTexture(texture); };
    void bindTexture(Texture * texture) { this->api->bindTexture(texture); };
    MeshData * allocateMeshData(MeshData * meshData){ this->api->allocateMeshData(meshData);};

    void renderTargetDrawMeshData(RenderTarget *renderTarget, std::vector<MeshData *> meshData){ this->api->renderTargetDrawMeshData(renderTarget, meshData);};
    void renderTargetClearDepthBuffer(RenderTarget *renderTarget){ this->api->renderTargetClearDepthBuffer(renderTarget);};
    void renderTargetClearColourBuffer(RenderTarget *renderTarget){ this->api->renderTargetClearColourBuffer(renderTarget);};

    // Viewport and Projection
    template<typename... Args>
    void resizeViewport(int width,int height,Args &&... args) { this->api->resizeViewport(width,height,std::forward<Args>(args)...); };
    template<typename... Args>
    void setProjectionMatrix(Args &&... args) { this->api->setProjectionMatrix(std::forward<Args>(args)...); };

    void reportErrors(){ this->api->reportErrors();};
    void cleanupResources(){ this->api->cleanupResources();};

    template<typename... Args>
    void shutdown(Args &&... args) { this->api->shutdown(std::forward<Args>(args)...); };

    template<typename... Args>
    void demoTriangle() {
        try {
            this->api->demoTriangle();
        } catch (const std::exception& e) {
            this->api->reportErrors();
        }};

};




