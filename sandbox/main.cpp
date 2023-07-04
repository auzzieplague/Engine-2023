#include <iostream>
#include "../engine/Engine.h"
#include "../engine/layers/CollisionLayer.h"
#include "../engine/layers/PhysicsLayer.h"
#include "../engine/layers/IMGuiLayer.h"

Model *playerObject;

Model *modelWithSubMeshes(bool physics = true) {
    ColliderConfig config{};
    Material material;

    material.loadFromAsset("mats_ground", "gray-bricks1");

    auto *model = Model::createWithGeometry(Geometry::ShapeType::Sphere);
    model->setName("model");
    model->setLocalRotation(glm::vec3(-30, 0, -25));
    model->setMaterial(material);
    model->setLocalScale(1);
    model->setPosition(glm::vec3(0, 0, -20));

    if (physics) {
        auto *collisionMesh = new Geometry();
        collisionMesh->buildCube(GeometryConfig{.cube{.size=1}, .sphere{.radius=2}});
        model->setCollisionMesh(collisionMesh);
        config.shape = config.Box;
        config.type = config.Dynamic;
        model->setCollider(config);
    }

    float offset = 1;
    glm::vec3 positions[] = {
            glm::vec3(-offset, -offset, -offset),
            glm::vec3(offset, -offset, -offset),
            glm::vec3(-offset, offset, -offset),
            glm::vec3(offset, offset, -offset),
            glm::vec3(-offset, -offset, offset),
            glm::vec3(offset, -offset, offset),
            glm::vec3(-offset, offset, offset),
            glm::vec3(offset, offset, offset),
    };

    int count = 7;
    for (int n = count; n >= 0; n--) {
        auto subMesh = new Geometry();
        subMesh->buildSphere();
        subMesh->setName("sub mesh "+std::to_string(n));
        subMesh->setPosition(positions[n]); // should be relative to parent mesh
        material.setAmbientColor(glm::vec3(n * (1 / (count?count:1)), 0, 0));
        subMesh->setMaterial(material);
        subMesh->getMaterial().randomAmbientColor();
        model->mRootMesh->addMesh(subMesh);
    }
    //todo make box same size as demo corners
    return model;
}

Model *terrainModel() {
    ColliderConfig config{};
    Material material;
    material.loadFromAsset("mats_ground", "grass1");

    auto *terrain1 = new Model();
    terrain1->getMeshFromHeightMap("test_map_64");
    Mesh * mesh = terrain1->getRootMesh();

//    Debug::show("Mesh Before and After");
//    Debug::show(mesh->getVertices().size());
//    terrain1->getRootMesh()->reduceMeshData(); // todo find new algorithm
//    Debug::show(mesh->getVertices().size());

    terrain1->setLocalScale({100, 10, 100});
    terrain1->setPosition({0, -20, -20});
    // todo 0 rotations cause build issues
    terrain1->setLocalRotation({1, 1, 1});
    terrain1->setMaterial(material);
    config = {.shape=config.Mesh, .type=config.Static};
    terrain1->setCollider(config);
    return terrain1;
}

void setupScene(Scene *scene) {

    playerObject = modelWithSubMeshes(true);
    scene->addComponent(playerObject);

    auto assimpModel = AssetManager::loadModelFromFile("../assets/models/testModel.obj");
    scene->addComponent(assimpModel);

    auto terrain = terrainModel();
    scene->addComponent(terrain);

//    scene->selectedComponent = playerObject;

    Debug::show("[->] Use NumPad 4862+- to navigate test Model");
    Debug::show("[->] RPY (roll, pitch, yaw) UIO (world xyz) rotations ");
}

void outputExecutionMode() {
#ifdef _WIN64
    std::cout << "Running in 64-bit mode" << std::endl;
#else
    std::cout << "Running in 32-bit mode" << std::endl;
#endif
}

int main() {
    /// preflight tests
    outputExecutionMode();

    AssetManager::testASSIMP();
//    AssetManager::buildDirectoryStructure("..\\assets");

    /// Required Layers
    Engine *engine = Engine::getInstance();
    engine->setGraphicsApi(new API_OpenGL());
    engine->attachLayer(new WindowLayer());    // maintains the window interface & required for input processing

    /// optional layers
    engine->attachLayer(new GraphicsLayer());  // uses the specified Graphics API to render the scene
    engine->attachLayer(new PhysicsLayer());   // uses physx to keep dynamic objects in bounds
    engine->attachLayer(new IMGuiLayer());
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

    interactionLayer->currentComponent = playerObject;

    /// kick-start the main loop
    engine->start();

    Debug::show("[>] Expected engine->stop()");
}
