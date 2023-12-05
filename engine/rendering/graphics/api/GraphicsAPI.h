#pragma once

#include <GraphicsBehaviour.h>

/*
 * the methods below act as a gateway to the chosen api for our other classes such as VertexBuffer, IndexBuffer, etc.
 * those methods can call ->createVertexBuffer(this) and this gateway will call the corresponding api->createVertexBuffer(instance)
 *
 * the variadic templated functions provide a level of abstraction for us to hook in to if required
 * I think we can just have createBuffer(instance) and the templating will allow us to provide the
 * 3 types of buffers and have the 3 methods in behaviour with only 1 entry here :/
 * rather than createVertexBuffer, createIndexBuffer, createObjectBuffer
 *
 * then we only need 1 method to createBuffer, BindBuffer in the BaseBuffer class
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


    // Resource Management
    void createFrameBuffer(FrameBuffer *fbo) { this->api->createFrameBuffer(fbo); };

    void resetFrameBuffer(FrameBuffer * buffer, int width, int height) { return this->api->resetFrameBuffer(buffer, width, height);}

    template<typename... Args>
    void createTexture(Args &&... args) {return this->api->createTexture(std::forward<Args>(args)...); };

    template<typename... Args>
    void bindTexture(Args &&... args) { this->api->bindTexture(std::forward<Args>(args)...); };

    template<typename... Args>
    void drawIndexed(Args &&... args) { this->api->drawIndexed(std::forward<Args>(args)...); };

    template<typename... Args>
    void setUniforms(Args &&... args) { this->api->setUniforms(std::forward<Args>(args)...); };

    // Framebuffer and Render Target Management
    template<typename... Args>
    void setRenderTarget(Args &&... args) { this->api->setRenderTarget(std::forward<Args>(args)...); };

    template<typename... Args>
    void renderTargetBind(RenderTarget *renderTarget){ this->api->renderTargetBind(renderTarget);};

    template<typename... Args>
    void reportErrors(){ this->api->reportErrors();};


    template<typename... Args>
    void cleanupResources(){ this->api->cleanupResources();};

    template<typename... Args>
    void renderTargetDrawMeshData(RenderTarget *renderTarget, std::vector<MeshData *> meshData){ this->api->renderTargetDrawMeshData(renderTarget, meshData);};

    void renderTargetClearDepthBuffer(RenderTarget *renderTarget){ this->api->renderTargetClearDepthBuffer(renderTarget);};

    void renderTargetClearColourBuffer(RenderTarget *renderTarget){ this->api->renderTargetClearColourBuffer(renderTarget);};

    // Viewport and Projection
    template<typename... Args>
    void setViewport(Args &&... args) { this->api->setViewport(std::forward<Args>(args)...); };

    template<typename... Args>
    void setProjectionMatrix(Args &&... args) { this->api->setProjectionMatrix(std::forward<Args>(args)...); };

    template<typename... Args>
    void resizeViewport(int width,int height,Args &&... args) { this->api->resizeViewport(width,height,std::forward<Args>(args)...); };

    // Shader Management
    template<typename... Args>
    void compileShader(Args &&... args) { this->api->compileShader(std::forward<Args>(args)...); };

    template<typename... Args>
    void linkShaderProgram(Args &&... args) { this->api->linkShaderProgram(std::forward<Args>(args)...); };

    template<typename... Args>
    MeshData * allocateMeshData(MeshData * meshData){ this->api->allocateMeshData(meshData);};
    template<typename... Args>

    void useShaderProgram(Args &&... args) { this->api->useShaderProgram(std::forward<Args>(args)...); };

    // Cleanup and Shutdown
    template<typename... Args>
    void shutdown(Args &&... args) { this->api->shutdown(std::forward<Args>(args)...); };

    template<typename... Args>
    void demoTriangle() {
        try {
            this->api->demoTriangle();
        } catch (const std::exception& e) {
            this->api->reportErrors();
        }};

    unsigned int getFlag(const char *string) {
        return string ? this->api->getFlagCode(string) : 0;
    }


};




