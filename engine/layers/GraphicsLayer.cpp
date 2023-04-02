//
// Created by auzzi on 2/04/2023.
//

#include "GraphicsLayer.h"
 void (*GraphicsLayer::render_method)();
 void (*GraphicsLayer::render_test)();
 void (*GraphicsLayer::load_shader_method)();
 unsigned int (*GraphicsLayer::create_mesh_method)(Mesh *);
 unsigned int (*GraphicsLayer::load_mesh_method)(std::string);
 unsigned int (*GraphicsLayer::create_material_method)();

void GraphicsLayer::initFunctionPointers() {
    render_method= method_default;
    render_test= method_default;
}


GraphicsLayer::GraphicsLayer(int framework) {

    initFunctionPointers();

    switch (framework) {
        case OPENGL :
            // assign opengl functions to our virtual functions
            load_shader_method = GraphicsLayerOpenGL::load_shader_method;
            render_test = GraphicsLayerOpenGL::render_test;
            render_method = GraphicsLayerOpenGL::render_method;
            create_mesh_method=GraphicsLayerOpenGL::create_mesh_method;
            load_mesh_method=GraphicsLayerOpenGL::load_mesh_method;
            create_material_method=GraphicsLayerOpenGL::create_material_method;
            break;
        case DIRECTX :
            break;
        default:
            Debug::show("Framework currently not supported");
    }

}

void GraphicsLayer::method_default() {
    std::cout << "base method called\n";
}


