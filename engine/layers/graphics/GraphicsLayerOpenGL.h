#pragma once
#include "../GraphicsLayer.h"
class GraphicsLayerOpenGL {
private:
    static unsigned int shaderProgram;
    static unsigned int testMeshVAO;
public:

    // should replicate the assignable methods in graphics layer - also define in cpp file
    static void load_shader_method();
    static unsigned int create_mesh_method(Mesh *);
    static unsigned int load_mesh_method(std::string){return 0;};
    static unsigned int create_material_method(){return 0;};
    static void render_method();
    static void render_test();
    static void framebuffer_size_callback (GLFWwindow* window, int width, int height);
};

