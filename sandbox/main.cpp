#include <iostream>
#include "../engine/Engine.h"
#include "../engine/layers/CollisionLayer.h"
#include "../engine/layers/PhysicsLayer.h"

Model *playerObject;

Model *modelWithSubMeshes() {
    Material material;
    material.loadFromAsset("mats_ground", "gray-bricks1");

    auto *root = Model::createFromGeometry(Geometry::ShapeType::Sphere);
    root->setWorldPosition(glm::vec3(-1, 0, -25));
    root->setLocalRotation(glm::vec3(-30, 0, -25));
    root->setMaterial(material);

    glm::vec3 positions[] = {
            glm::vec3(-1, 0, -2),
            glm::vec3(1, 0, -2),
            glm::vec3(0, 0, -2),
    };

    int count = 3;
    for (int n = count; n > 0; n--) {
        auto subMesh = new Geometry();
        subMesh->buildSphere();
        subMesh->setLocalPosition(positions[n]); // should be relative to parent mesh
        material.setAmbientColor(glm::vec3(n*(1/count), 0, 0));
        subMesh->setMaterial(material);
        root->rootMesh->addMesh(subMesh);
    }


    return root;
}


void setupScene(Scene *scene) {
    ColliderConfig config{};
    Material material;

    playerObject = modelWithSubMeshes();
    playerObject->setLocalScale(1);
    playerObject->setWorldPosition(glm::vec3(0,0,-20));

    config.shape = config.Sphere;
    config.type = config.Dynamic;
    playerObject->setCollider(config);
    scene->addComponent(playerObject);

    material.loadFromAsset("mats_ground", "grass1");
    auto *terrain1 = new Model();
    terrain1->getMeshFromHeightMap("test_map_64");
//    terrain1->setLocalRotation({0, 0, 0});
    terrain1->setLocalScale({100, 10, 100});
    terrain1->setWorldPosition({0, -20, -20});
    terrain1->setMaterial(material);
    config = {.shape=config.Mesh, .type=config.Static};
    terrain1->setCollider(config);
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
    } catch (const std::exception &e) {
        Debug::show("[!] Scene Setup Error");
        Debug::show(e.what());
    }

    interactionLayer->selectedModel = playerObject;


    /// kick-start the main loop
    engine->start();

    Debug::show("[>] Expected engine->stop()");
}
