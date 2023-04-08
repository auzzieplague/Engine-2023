
#include <iostream>
#include "../engine/Engine.h"
#include "../engine/layers/WindowLayer.h"
#include "../engine/layers/graphics/api/API_OpenGL.h"
#include <Windows.h>
#include <d3d11.h>

int main() {

    auto *component = new CollisionMesh();
    Engine *engine = Engine::getInstance();
    engine->addComponent(component);

//define graphics api to be injected into window and graphics classes
    GraphicsAPI *opengl = new API_OpenGL();

    auto *window = new WindowLayer(opengl);
    engine->attachLayer(window);
    auto *gl = new GraphicsLayer(opengl);
    engine->attachLayer(gl);


//gl->test();
//    auto *test = new Engine();
    engine->start();
//    return 0;
    Debug::show("done");
}
