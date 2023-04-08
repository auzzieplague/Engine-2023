
#include <iostream>
#include "../engine/Engine.h"

#include <Windows.h>
#include <d3d11.h>

int main() {

    Engine *engine = Engine::getInstance();
    engine->setGraphicsApi(new API_OpenGL());

    engine->attachLayer(new WindowLayer());
    engine->attachLayer(new GraphicsLayer());
    engine->attachLayer(new InteractionLayer());

    engine->start();

    Debug::show("done");
}
