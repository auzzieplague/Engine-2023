#pragma once

#include <GraphicsBehaviour.h>
#include "HasGraphicsAPI.h"

class Mesh;

class GraphicsAPI: public HasGraphicsAPI {

public:
    explicit GraphicsAPI(GraphicsBehaviour *api){
        this->api = api;
//        this->queryCapabilities();
    }

    void setInitializationBehavior(GraphicsBehaviour *behavior) {
        api = behavior;
    }

    template<typename... Args>
    bool initialise(Args &&... args) { return this->api->initialise(std::forward<Args>(args)...); };

    template<typename... Args>
    void queryCapabilities(Args &&... args) { this->api->queryCapabilities(std::forward<Args>(args)...); };

    template<typename... Args>
    void displayCapabilities(Args &&... args) { this->api->displayCapabilities(std::forward<Args>(args)...); };

    // Resource Management
    unsigned int createVertexBuffer(VertexBuffer *vb) {return this->api->createVertexBuffer(vb); };

    template<typename... Args>
    unsigned int createIndexBuffer(Args &&... args) {return this->api->createIndexBuffer(std::forward<Args>(args)...); };

    template<typename... Args>
    unsigned int createTexture(Args &&... args) {return this->api->createTexture(std::forward<Args>(args)...); };

    template<typename... Args>
    unsigned int createShaderProgram(Args &&... args) {return this->api->createShaderProgram(std::forward<Args>(args)...); };

    // Rendering
    template<typename... Args>
    void bindVertexBuffer(Args &&... args) { this->api->bindVertexBuffer(std::forward<Args>(args)...); };

    template<typename... Args>
    void bindIndexBuffer(Args &&... args) { this->api->bindIndexBuffer(std::forward<Args>(args)...); };

    template<typename... Args>
    void bindTexture(Args &&... args) { this->api->bindTexture(std::forward<Args>(args)...); };

    template<typename... Args>
    void bindShaderProgram(Args &&... args) { this->api->bindShaderProgram(std::forward<Args>(args)...); };

    template<typename... Args>
    void drawIndexed(Args &&... args) { this->api->drawIndexed(std::forward<Args>(args)...); };

    template<typename... Args>
    void setUniforms(Args &&... args) { this->api->setUniforms(std::forward<Args>(args)...); };

    // Framebuffer and Render Target Management
    template<typename... Args>
    void setRenderTarget(Args &&... args) { this->api->setRenderTarget(std::forward<Args>(args)...); };

    template<typename... Args>
    void clearRenderTarget(Args &&... args) { this->api->clearRenderTarget(std::forward<Args>(args)...); };

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
    void linkProgram(Args &&... args) { this->api->linkProgram(std::forward<Args>(args)...); };

    // Cleanup and Shutdown
    template<typename... Args>
    void shutdown(Args &&... args) { this->api->shutdown(std::forward<Args>(args)...); };

    template<typename... Args>
    void demoTriangle(Args &&... args) { this->api->demoTriangle(std::forward<Args>(args)...); };

    unsigned int getFlag(const char *string) {
        return this->api->getFlagCode(string);
    }
};




