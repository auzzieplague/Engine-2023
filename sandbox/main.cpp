#include <iostream>
#include "../engine/Engine.h"
#include "../engine/layers/CollisionLayer.h"

Model * testSphere;

void setupScene(Scene *scene) {

    auto *terrain1 = Model::createFromGeometry(Geometry::ShapeType::Terrain);
//    terrain1->setCollider();
    terrain1->setPosition({-5, -2, -10});

    auto sphere1 = Model::createFromGeometry(Geometry::ShapeType::Sphere);
    sphere1->setCollider();
    sphere1->setPosition({-2, 2, -10});

    auto sphere2 = Model::createFromGeometry(Geometry::ShapeType::Sphere);
    sphere2->setCollider();
    sphere2->setPosition({2, 2, -10});

    auto sphere3 = Model::createFromGeometry(Geometry::ShapeType::Sphere);
    sphere3->setCollider();
    sphere3->setPosition({0, 2, -10});


    testSphere = Model::createFromGeometry(Geometry::ShapeType::Sphere,
                                             GeometryConfig {.sphere {.radius =.5,.rings =6, .sectors =6}});
    testSphere->setCollider();
    testSphere->setPosition({0, 2, -8});

    scene->addComponent(sphere1);
    scene->addComponent(sphere2);
    scene->addComponent(sphere3);

    scene->addComponent(testSphere);
    scene->addComponent(terrain1);
}

int main() {
    Engine *engine = Engine::getInstance();
    engine->setGraphicsApi(new API_OpenGL());
    engine->attachLayer(new WindowLayer());
    engine->attachLayer(new GraphicsLayer());
    engine->attachLayer(new CollisionLayer());

    //setup interaction layer and scene together to inject a test model
    auto * interactionLayer = new InteractionLayer();
    engine->attachLayer(interactionLayer);
    setupScene(engine->currentScene);
    interactionLayer->selectedModel = testSphere;

    engine->start();
    Debug::show("done");
}
