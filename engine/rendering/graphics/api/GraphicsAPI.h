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

    template<typename... Args>
    bool initialise(Args &&... args) { return this->api->initialise(std::forward<Args>(args)...); };

    template<typename... Args>
    void queryCapabilities(Args &&... args) { this->api->queryCapabilities(std::forward<Args>(args)...); };

    template<typename... Args>
    void displayCapabilities(Args &&... args) { this->api->displayCapabilities(std::forward<Args>(args)...); };


    // Resource Management
    template<typename... Args>
    unsigned int createVertexBuffer(Args &&... args) {return this->api->createVertexBuffer(std::forward<Args>(args)...); };

    template<typename... Args>
    void bindVertexBuffer(Args &&... args) { this->api->bindVertexBuffer(std::forward<Args>(args)...); };

    template<typename... Args>
    unsigned int createIndexBuffer(Args &&... args) {return this->api->createIndexBuffer(std::forward<Args>(args)...); };

    template<typename... Args>
    void bindIndexBuffer(Args &&... args) { this->api->bindIndexBuffer(std::forward<Args>(args)...); };

    unsigned int createBufferObject(BufferObject *buffer) {
        return this->api->createBufferObject(buffer);
    };

    template<typename... Args>
    void bindBufferObject(Args &&... args) { this->api->bindBufferObject(std::forward<Args>(args)...); };

    template<typename... Args>
    void createFrameBuffer(Args &&... args) { this->api->createFrameBuffer(std::forward<Args>(args)...); };


    template<typename... Args>
    void applyLayout(Args &&... args) {return this->api->applyLayout(std::forward<Args>(args)...); };

    template<typename... Args>
    unsigned int createTexture(Args &&... args) {return this->api->createTexture(std::forward<Args>(args)...); };

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
    void finalRender(RenderTarget *renderTarget){ this->api->finalRender(renderTarget);};


    template<typename... Args>
    void cleanupResources(){ this->api->cleanupResources();};

    template<typename... Args>
    void renderTargetDrawMeshData(RenderTarget *renderTarget, std::vector<MeshData *> meshData){ this->api->renderTargetDrawMeshData(renderTarget, meshData);};
    template<typename... Args>
    void renderTargetClearDepthBuffer(RenderTarget *renderTarget){ this->api->renderTargetClearDepthBuffer(renderTarget);};
    template<typename... Args>
    void renderTargetClearColourBuffer(RenderTarget *renderTarget){ this->api->renderTargetClearColourBuffer(renderTarget);};

    // Viewport and Projection
    template<typename... Args>
    void setViewport(Args &&... args) { this->api->setViewport(std::forward<Args>(args)...); };

    template<typename... Args>
    void setProjectionMatrix(Args &&... args) { this->api->setProjectionMatrix(std::forward<Args>(args)...); };

    template<typename... Args>
    void resizeViewport(Args &&... args) { this->api->resizeViewport(std::forward<Args>(args)...); };

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
    void demoTriangle(Args &&... args) { this->api->demoTriangle(std::forward<Args>(args)...); };

    unsigned int getFlag(const char *string) {
        return string ? this->api->getFlagCode(string) : 0;
    }
};




