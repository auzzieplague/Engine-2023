#pragma once
#include <GLFW/glfw3.h>
#include "GraphicsAPI.h"

/**
 * requires glfw3.lib installed
 */
class API_OpenGL : public GraphicsBehaviour {
private:
    static bool isExtensionSupported(const char* extensionName);
public:
    bool initialise (...) override;
    void queryCapabilities(...) override;

    void demoTriangle(...) override ;

    void demoTriangleRaw();

    unsigned int createVertexBuffer( VertexBuffer* ) override;
    void bindVertexBuffer( VertexBuffer* vb ) override;

    unsigned int getFlagCode(const char *string) override;
//    unsigned int createIndexBuffer(...) override;

};

