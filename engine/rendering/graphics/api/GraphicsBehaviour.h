#pragma once
#include <graphics/Texture.h>
#include <graphics/ShaderProgram.h>
#include <graphics/RenderTarget.h>
#include <GPUInfo.h>
#include <cstdio>
#include <components/meshes/MeshData.h>

class VertexBuffer;
class IndexBuffer;
class BufferObject;
class GPULayout;

class GraphicsBehaviour {

protected:
    GPUInfo *gpuInfo{};
public:
// Initialization
    virtual bool initialise(...) { return false; };
    virtual void queryCapabilities(...) {  };
    virtual void displayCapabilities(...);

    // Resource Management
    virtual unsigned int createVertexBuffer(VertexBuffer* vb) {return 0;};
    virtual unsigned int createIndexBuffer(IndexBuffer *ib) {return 0;};
    virtual unsigned int createBufferObject(BufferObject *bo) {return 0;}; // VAO in opengl
    virtual void compileShader(Shader *shader) {};
    virtual unsigned int linkShaderProgram(ShaderProgram *) {return 0;};
    virtual void useShaderProgram(ShaderProgram *) {};
    virtual void applyLayout(GPULayout *layout, BufferObject *object);

    virtual unsigned int createTexture(...) {return 0;};


    // Rendering
    virtual void bindVertexBuffer(VertexBuffer* vb) {};
    virtual void bindIndexBuffer(IndexBuffer* ib) {};
    virtual void bindBufferObject(BufferObject *bo) {}; // VAO in opengl

    virtual void bindTexture(...) {};
    virtual void bindShaderProgram(...) {};
    virtual void drawIndexed(...) {};
    virtual void setUniforms(...) {};

    // Framebuffer and Render Target Management
    virtual void setRenderTarget(...) {};
    virtual void clearRenderTarget(...) {};

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

    virtual MeshData* getSampleMeshData(){

        float vertices[] = {
                -0.5f, -0.5f, 0.0f, // Bottom-left corner
                0.5f, -0.5f, 0.0f, // Bottom-right corner
                0.5f, 0.5f, 0.0f, // Top-right corner
                -0.5f, 0.5f, 0.0f  // Top-left corner
        };

        unsigned int indices[] = {
                0, 1, 2, // First triangle
                2, 3, 0  // Second triangle
        };

        auto meshData = new MeshData();
        meshData->setVertices(vertices, sizeof (vertices));
        meshData->setIndices(indices, sizeof (indices));

        return meshData;
    };
};
