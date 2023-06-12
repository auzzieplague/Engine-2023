#include <iostream>
#include "../engine/Engine.h"
#include "../engine/layers/CollisionLayer.h"
#include "../engine/layers/PhysicsLayer.h"

Model *playerObject;

Model * modelWithSubMeshes () {
    Material material;
    material.loadFromAsset("mats_ground", "gray-bricks1");

    auto *root = Model::createFromGeometry(Geometry::ShapeType::Cube);
    root->setWorldPosition(glm::vec3(-1, 0, -25));
    root->setLocalRotation(glm::vec3(-30, 0, -25));
    root->setMaterial(material);
    root->rootMesh->setLocalScale(glm::vec3{0.5,0.5,0.5});
//
//    auto subMesh = new Geometry();
//    subMesh->buildCube();
//    subMesh->setLocalPosition(glm::vec3(1, 0, -2)); // should be relative to parent mesh
//    material.setAmbientColor(glm::vec3(0.5,0,0));
//    subMesh->setMaterial(material);
//    root->rootMesh->addMesh(subMesh);
//
//    auto subSubMesh = new Geometry();
//    subSubMesh->buildCube();
//    subSubMesh->setLocalPosition(glm::vec3(-1, 1, 0)); // should be relative to parent mesh
//    material.setAmbientColor(glm::vec3(0,0.5,0));
//    subSubMesh->setMaterial(material);
//    subMesh->addMesh(subSubMesh);

    return root;
}

void setupScene(Scene *scene) {
    ColliderConfig config{};

    playerObject = modelWithSubMeshes();

    Material material;
    material.loadFromAsset("mats_ground", "gray-bricks1");

//    playerObject->setLocalScale({2, 2, 2 });
//    playerObject->setMaterial(material);
//    playerObject->setLocalPosition({0, 0, -10});
//    playerObject->setLocalRotation({30, 0, 0});


//    config.shape = config.Sphere;
//    config.type = config.Static;
//    playerObject->setCollider(config);
    scene->addComponent(playerObject);

    return;
    material.loadFromAsset("mats_ground", "grass1");
    auto *terrain1 = new Model();
    terrain1->getMeshFromHeightMap("test_map_64");
    terrain1->setLocalPosition({0, -20, 0});
    terrain1->setLocalRotation({0, 0, 0});
    terrain1->setLocalScale({100, 10, 100});
    terrain1->setMaterial(material);
    auto test = terrain1->getLocalMatrix();
    config = {.shape=config.Mesh, .type=config.Static};
    terrain1->setCollider(config);
//    terrain1->rootMesh->switchIndexOrder();
    scene->addComponent(terrain1);

    Debug::show("[->] Use 'R' to generate collision report");
    Debug::show("[->] Use NumPad 4862+- to navigate tests");
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

    // setup interaction layer and scene together to inject a tests model
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
