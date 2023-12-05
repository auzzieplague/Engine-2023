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
    bool initialise(...) override;

    void queryCapabilities(...) override;


    void demoTriangle(...) override;
    void demoTriangle2(...);

    void resizeViewport(int width, int height, ...) override;

    unsigned int getFlagCode(const char *string) override;


    unsigned int createContainerObject(BufferContainer *bo) override;
    unsigned int createContainerForMesh(Mesh *mesh) override;

    void bindContainerObject(BufferContainer *bo) override;

    MeshData * allocateMeshData(MeshData *) override;

    unsigned int createFrameBuffer(FrameBuffer *fbo) override;

    void createTexture(Texture *texture) override;

    void compileShader(Shader *) override;

    unsigned int linkShaderProgram(ShaderProgram *) override;

    void  useShaderProgram(ShaderProgram *) override;

    void reportErrors() override;
    void finalRender(RenderTarget *renderTarget) override;
    void renderTargetBind(RenderTarget *renderTarget) override;
    void renderTargetDrawMeshData(RenderTarget *renderTarget, std::vector<MeshData *> meshData) override;
    void renderTargetClearDepthBuffer(RenderTarget *renderTarget) override;
    void renderTargetClearColourBuffer(RenderTarget *renderTarget) override;

    void cleanupResources() override;


    void updateCurrentTime();

    void resetFrameBuffer(FrameBuffer *fbo, int width, int height) override;
};

