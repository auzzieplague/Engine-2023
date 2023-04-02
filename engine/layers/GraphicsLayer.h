#pragma once
#include "../../core/Window.h"
#include "Layer.h"
#include "graphics/GraphicsLayerOpenGL.h"
#include "../components/Components.h"

/**
 * When instantiating this class we pass through a framework, which in turn sets up the function pointers
 * for OPENGL or other framework options
 */
class GraphicsLayer : public Layer {
private:
    void initFunctionPointers();
    static void method_default();
    static void (*render_test)();
    static void (*render_method)();
    static void (*load_shader_method)();
    static unsigned int (*create_mesh_method)(Mesh *);
    static unsigned int (*load_mesh_method)(std::string);
    static unsigned int (*create_material_method)();

    unsigned int testMeshVAO;

public:
    enum framework { OPENGL, DIRECTX };
    GraphicsLayer(int framework);

    // virtual function runners
    void draw() { render_method(); };
    void test() { render_test(); };

    virtual void onAttach(Scene*) {
        load_shader_method();
        //returns the voa
        testMeshVAO = create_mesh_method(new Mesh());
    };

    virtual void onDetach(Scene*) {}
    virtual void beforeUpdate(Scene*) {}
    virtual void update(Scene*) {}
    virtual void afterUpdate(Scene*) {}
    // expects that gui platform is checked through scene and rendered accordingly in derived class
    virtual void appendToGui(Scene*) {}
    virtual void beforeRender(Scene*) {}

    virtual void render(Scene*) {
        render_method();
    }

    virtual void afterRender(Scene*) {}
    virtual void processInput(Scene*) {}
};
