#include <iostream>
#include "../engine/Engine.h"
#include "../engine/layers/CollisionLayer.h"
#include "../engine/layers/PhysicsLayer.h"

Model *playerObject;

void setupScene(Scene *scene) {
    ColliderConfig config{};

    playerObject = Model::createFromGeometry(Geometry::ShapeType::Cube);

    Material material;
    material.loadFromAsset("mats_ground", "gray-bricks1");
//    material.loadFromAsset("mats_ground", "gray-bricks1");

    playerObject->setScale({5, 5, 5 });
    playerObject->setMaterial(material);
    playerObject->setPosition({0, 0, -5});
    playerObject->setRotation({30, 0, 0});


//    config.shape = config.Sphere;
//    config.type = config.Static;
//    playerObject->setCollider(config);
    scene->addComponent(playerObject);

//    return;
    material.loadFromAsset("mats_ground", "grass1");
    auto *terrain1 = new Model();
    terrain1->getMeshFromHeightMap("test_map_64");
    terrain1->setPosition({0, -20, 0});
    terrain1->setRotation({0, 0, 0});
    terrain1->setScale({100, 10, 100});
    terrain1->setMaterial(material);
    auto test = terrain1->getMatrix();
    config = {.shape=config.Mesh, .type=config.Static};
    terrain1->setCollider(config);
//    terrain1->mMesh->switchIndexOrder();
    scene->addComponent(terrain1);

    Debug::show("[->] Use 'R' to generate collision report");
    Debug::show("[->] Use NumPad 4862+- to navigate test");
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

    /// Required Layers
    Engine *engine = Engine::getInstance();
    engine->setGraphicsApi(new API_OpenGL());
    engine->attachLayer(new WindowLayer());    // maintains the window interface & required for input processing


    /// optional layers
    engine->attachLayer(new GraphicsLayer());  // uses the specified Graphics API to render the scene
    engine->attachLayer(new PhysicsLayer());   // uses physx to keep dynamic objects in bounds
//    engine->attachLayer(new CollisionLayer()); // processes collisions effects

    // setup interaction layer and scene together to inject a test model
    auto *interactionLayer = new InteractionLayer();
    engine->attachLayer(interactionLayer);

    try {
        setupScene(engine->currentScene);
    } catch(const std::exception& e) {
        Debug::show("[!] Scene Setup Error");
        Debug::show(e.what());
    }

    interactionLayer->selectedModel = playerObject;


    /// kick-start the main loop
    engine->start();

    Debug::show("[>] Expected engine->stop()");
}
