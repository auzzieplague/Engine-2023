#pragma once

#include "../../GraphicsLayer.h" // todo remove ?? add glfw refences here
#include "../../../AssetManager.h"
#include "RenderingConfig.h"
#include "../GraphicsCapabilities.h"

class Mesh;

class GraphicsAPI {

public:
    GraphicsCapabilities capabilities{};

    GraphicsAPI(){};

    virtual void initialise();
    virtual void setCapabilities();

    virtual RenderingConfig loadShader(std::string, std::string);

    virtual unsigned int loadTexture (std::string filename);

    virtual unsigned int compileShader(std::string &source, unsigned int type);

    virtual unsigned int setupMesh(Mesh *);

    virtual unsigned int setupTerrain(HeightMap *heightmap);

    virtual void renderMesh(Mesh *);
    virtual void renderInstancedMesh(Mesh *, std::vector<glm::mat4> transforms);

    virtual void initialiseShader(RenderingConfig &);
    virtual void beginRender(RenderingConfig &);
    virtual void endRender(RenderingConfig &);
    virtual void flushBuffers();
    virtual void readColourBufferRBGA(unsigned char *data, float x, float y, float width , float height);
    virtual void readDepthBuffer(float *data, float x, float y, float width , float height );

    virtual void framebufferSizeCallback(GLFWwindow *window, int width, int height);

    virtual unsigned int getFlag(GraphicsFlag flag);

    virtual void shaderSetBool(const std::string &name, bool value) const {};

    virtual void shaderSetInt(const std::string &name, int value) const {};

    virtual void shaderSetFloat(const std::string &name, float value) const {};

    virtual void shaderSetVec2(const std::string &name, const glm::vec2 &value) const {};

    virtual void shaderSetVec3(const std::string &name, const glm::vec3 &value) const {};

    virtual void shaderSetVec4(const std::string &name, const glm::vec4 &value) const {};

    virtual void shaderSetMat2(const std::string &name, const glm::mat2 &mat) const {};

    virtual void shaderSetMat3(const std::string &name, const glm::mat3 &mat) const {};

    virtual void shaderSetMat4(const std::string &name, const glm::mat4 &mat) const {};

    virtual void shaderSetMaterial(Material material) const {};

    virtual void shaderSetTransform(const glm::mat4 &mat) const {};

    virtual void shaderSetTransformList(const std::vector<glm::mat4> &mats) const {};

    virtual void shaderSetView(const glm::mat4 &mat) const {};

    virtual void shaderSetProjection(const glm::mat4 &mat) const {};

    virtual void  shaderSetCamera(Camera *pCamera){};

    void displayCapabilities();
};




