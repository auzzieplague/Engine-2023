
#include <iostream>
#include "../engine/Engine.h"
#include "../engine/layers/WindowLayer.h"

int main() {

auto * component = new CollisionMesh();
Engine *engine = Engine::getInstance();
engine->addComponent(component);

auto * window = new WindowLayer();
engine->attachLayer(window);


auto * gl = new GraphicsLayer(GraphicsLayer::OPENGL);
engine->attachLayer(gl);

//gl->test();
//    auto *test = new Engine();
engine->start();
//    return 0;
    Debug::show("done");
}
