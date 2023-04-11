#include <iostream>
#include "../engine/Engine.h"

Model * testSphere;

void setupScene(Scene *scene) {

    auto *terrain1 = Model::createFromGeometry(Geometry::ShapeType::Terrain);
//    terrain1->setCollidable();
    terrain1->transform.setPosition({-5, -2, -10});

    auto sphere1 = Model::createFromGeometry(Geometry::ShapeType::Sphere);
    sphere1->setCollidable();
    sphere1->transform.setPosition({0, -2, -10});

    testSphere = Model::createFromGeometry(Geometry::ShapeType::Sphere,
                                             GeometryConfig {.sphere {.radius =.2,.rings =6, .sectors =6}});
    testSphere->setCollidable();
    testSphere->transform.setPosition({0, -1, -10});

    scene->addComponent(sphere1);
    scene->addComponent(testSphere);
//    scene->addComponent(terrain1);
}

int main() {
    Engine *engine = Engine::getInstance();
    engine->setGraphicsApi(new API_OpenGL());

    engine->attachLayer(new WindowLayer());
    engine->attachLayer(new GraphicsLayer());
    InteractionLayer * interactionLayer = new InteractionLayer();
    engine->attachLayer(interactionLayer);
    setupScene(engine->currentScene);


    interactionLayer->selectedModel = testSphere;
    engine->start();

    Debug::show("done");
}
