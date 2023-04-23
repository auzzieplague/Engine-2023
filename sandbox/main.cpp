#include <iostream>
#include "../engine/Engine.h"
#include "../engine/layers/CollisionLayer.h"
#include "../engine/layers/PhysicsLayer.h"


Model *testSphere;

void sphereCollisionTesting(Scene *scene) {

    auto object1 = Model::createFromGeometry(Geometry::ShapeType::Sphere);
    object1->setCollider();
    object1->setPosition({2, 0, -12});

    auto object2 = Model::createFromGeometry(Geometry::ShapeType::Cube);
    object2->setCollider();
    object2->setPosition({2, 2, -12});

    auto object3 = Model::createFromGeometry(Geometry::ShapeType::Dome);
    object3->setCollider();
    object3->setPosition({-2.5, 0, -12});


    auto object4 = Model::createFromGeometry(Geometry::ShapeType::Torus);
    object4->setCollider();
    object4->setPosition({0, 2, -12});

    scene->addComponent(object2);
    scene->addComponent(object3);
    scene->addComponent(object1);
    scene->addComponent(object4);

    int start = 10;
    int end = 20;
    int space = 1;

    auto test = Model::createFromGeometry(Geometry::ShapeType::Cube,
                                          GeometryConfig{.cube {.size=2}});
    test->setPosition({start+4.2, start+4.2, start+4.2});
    test->setCollider();
    scene->addComponent(test);

    for (int x = start; x < end; x+=space) {
        for (int z = start; z < end; z+=space) {
            for (int y = start; y < end; y+=space) {
                auto spot = Model::createFromGeometry(Geometry::ShapeType::Sphere,
                                                      GeometryConfig{.sphere {.radius =.1, .rings =3, .sectors =6}});
                spot->setPosition({x, y, z});
                spot->setCollider();
                scene->addComponent(spot);
            }
        }
    }
}

void setupScene(Scene *scene) {

//    sphereCollisionTesting(scene);

    auto *terrain1 = Model::createFromGeometry(Geometry::ShapeType::Terrain);
    terrain1->setPosition({-8, -2, -15});
    terrain1->setCollider();
    scene->addComponent(terrain1);


    testSphere = Model::createFromGeometry(Geometry::ShapeType::Sphere,
                                           GeometryConfig{.sphere {.radius =.5, .rings =6, .sectors =6}});
    testSphere->setPosition({0, 0, -12});
    testSphere->setCollider();
    scene->addComponent(testSphere);
}

void outputExecutionMode() {
#ifdef _WIN64
    std::cout << "Running in 64-bit mode" << std::endl;
#else
    std::cout << "Running in 32-bit mode" << std::endl;
#endif
}


int main() {
    outputExecutionMode();

    Engine *engine = Engine::getInstance();
    engine->setGraphicsApi(new API_OpenGL());
    engine->attachLayer(new WindowLayer());
    engine->attachLayer(new GraphicsLayer());
    engine->attachLayer(new CollisionLayer());

    engine->attachLayer(new PhysicsLayer());

    //setup interaction layer and scene together to inject a test model
    auto *interactionLayer = new InteractionLayer();
    engine->attachLayer(interactionLayer);
    setupScene(engine->currentScene);
    interactionLayer->selectedModel = testSphere;

    Debug::show("[->] Use 'R' to generate collision report");
    Debug::show("[->] Use NumPad 4862+- to navigate test");

    engine->start();
    Debug::show("done");
}
