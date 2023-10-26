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


    unsigned int getFlagCode(const char *string) override;

    unsigned int createVertexBuffer(VertexBuffer *) override;

    void bindVertexBuffer(VertexBuffer *vb) override;

    unsigned int createIndexBuffer(IndexBuffer *ib) override;

    void bindIndexBuffer(IndexBuffer *ib) override;

    unsigned int createBufferObject(BufferObject *bo) override;

    void bindBufferObject(BufferObject *bo) override;

    void compileShader(Shader *) override;

    unsigned int linkShaderProgram(ShaderProgram *) override;

    void  useShaderProgram(ShaderProgram *) override;

    void applyLayout(GPULayout *layout) override;

};

