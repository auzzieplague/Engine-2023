#include <iostream>
#include "../engine/Engine.h"

void setupScene(Scene *scene) {

    auto *terrain1 = Model::createFromGeometry(Geometry::ShapeType::Terrain);
    terrain1->setCollidable();
    terrain1->transform.setPosition({-5, -2, -10});

    auto sphere1 = Model::createFromGeometry(Geometry::ShapeType::Sphere);
    sphere1->setCollidable();
    sphere1->transform.setPosition({0, -2, -10});

    scene->addComponent(sphere1);
    scene->addComponent(terrain1);
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
