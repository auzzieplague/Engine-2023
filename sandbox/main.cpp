#include <iostream>
#include "../engine/Engine.h"
#include "../engine/layers/CollisionLayer.h"

Model *testSphere;

void setupScene(Scene *scene) {

    auto *terrain1 = Model::createFromGeometry(Geometry::ShapeType::Terrain);
    terrain1->setPosition({-8, -2, -8});
    terrain1->setCollider();
    scene->addComponent(terrain1);


    testSphere = Model::createFromGeometry(Geometry::ShapeType::Sphere,
                                           GeometryConfig{.sphere {.radius =.5, .rings =6, .sectors =6}});
    testSphere->setPosition({0, 0, -12});
    testSphere->setCollider();

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
    scene->addComponent(testSphere);

//
//    for (int x = 0; x < 20; x+=5) {
//        for (int z = 0; z < 20; z+=5) {
//            auto spot = Model::createFromGeometry(Geometry::ShapeType::Sphere,
//                                                    GeometryConfig{.sphere {.radius =.2, .rings =3, .sectors =6}});
//            spot->setPosition({x, 0, z});
//            spot->setCollider();
//            scene->addComponent(spot);
//        }
//    }

}

int main() {
    Engine *engine = Engine::getInstance();
    engine->setGraphicsApi(new API_OpenGL());
    engine->attachLayer(new WindowLayer());
    engine->attachLayer(new GraphicsLayer());
    engine->attachLayer(new CollisionLayer());

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
