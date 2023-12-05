#pragma once

#include <GLFW/glfw3.h>
#include "GraphicsAPI.h"

/**
 * requires glfw3.lib installed
 */
class API_OpenGL : public GraphicsBehaviour {
private:
    static bool isExtensionSupported(const char *extensionName);

public:
    bool initialise() override;
    void queryCapabilities() override;

    void compileShader(Shader *) override;
    unsigned int linkShaderProgram(ShaderProgram *) override;
    void  useShaderProgram(ShaderProgram *) override;

    unsigned int createFrameBuffer(FrameBuffer *fbo) override;
    void resetFrameBuffer(FrameBuffer *fbo, int width, int height) override;
    void createTexture(Texture *texture) override;
    MeshData * allocateMeshData(MeshData *) override;
    void resizeViewport(int width, int height, ...) override;

    void demoTriangle() override;

    void renderTargetBind(RenderTarget *renderTarget) override;
    void renderTargetDrawMeshData(RenderTarget *renderTarget, std::vector<MeshData *> meshData) override;
    void renderTargetClearDepthBuffer(RenderTarget *renderTarget) override;
    void renderTargetClearColourBuffer(RenderTarget *renderTarget) override;

    void updateCurrentTime();
    void reportErrors() override;

    void cleanupResources() override;

};

