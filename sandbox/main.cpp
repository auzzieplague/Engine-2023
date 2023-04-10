
#include <iostream>
#include "../engine/Engine.h"
#include "../engine/components/Model.h"
//#include "../engine/components/Model.h"

#include <Windows.h>
#include <d3d11.h>

void setupScene(Scene *scene) {
    auto *model1 = new Model();
    auto *sphere = new Geometry();
    GeometryConfig config{
            .sphere = {
                    .radius = 0.5f,
                    .rings = 5,
                    .sectors =  5},

            .terrain = {
                    .seed = 123
            }
    };

//    sphere->buildDome();
//    sphere->buildCube();
//    sphere->buildSphere(config);
//    sphere->buildCapsule(); // borked
//    sphere->buildTorus(); // borked
//    sphere->buildCone(); // borked
    sphere->buildTerrain();


    model1->mesh = dynamic_cast<Mesh *>(sphere);
    model1->collider = new Collider();

    model1->transform.setPosition({0, 0, -5});
    /// gonna need to update geometries with sizing options
    scene->addComponent(model1);
}

int main() {
    Engine *engine = Engine::getInstance();
    engine->setGraphicsApi(new API_OpenGL());

    engine->attachLayer(new WindowLayer());
    engine->attachLayer(new GraphicsLayer());
    engine->attachLayer(new InteractionLayer());

    setupScene(engine->currentScene);
    engine->start();

    Debug::show("done");
}
