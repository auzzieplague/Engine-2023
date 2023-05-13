#include <iostream>
#include "../engine/Engine.h"
#include "../engine/layers/CollisionLayer.h"
#include "../engine/layers/PhysicsLayer.h"

Model *testSphere;

void setupScene(Scene *scene) {
    ColliderConfig config{};

    testSphere = Model::createFromGeometry(Geometry::ShapeType::Sphere,
                                           GeometryConfig{.sphere{.radius=0.5, .rings=10, .sectors=10}});
    config.shape = config.Sphere;
    config.type = config.Static;
    testSphere->setCollider(config);
    testSphere->setPosition({0, 0, -2});
    testSphere->setScale({0.1, 0.1, 0.1 });
    scene->addComponent(testSphere);

    std::vector<glm::vec3> positions = {
            {-4, 0, -4},
            {4, 0, -4},
            {-4, 0, 4},
            {4, 0, 4},
    };

    for (auto position : positions) {
        auto *model = Model::createFromGeometry(Geometry::ShapeType::Sphere,
                                  GeometryConfig{.sphere{.radius=0.1, .rings=10, .sectors=10}});
        model->setPosition(position);
        model
        ->setCollider(config);
        scene->addComponent(model);
    }


    auto *terrain1 = new Model();
    terrain1->getMeshFromHeightMap("test_map_64");
            Model::createFromGeometry(Geometry::ShapeType::Terrain,
                                               GeometryConfig{.terrain{.minHeight =0, .maxHeight = 0.1}});
    terrain1->setPosition({-50, -50, -100});
    terrain1->setRotation({60, 60, 60});
    terrain1->setScale({10, 10, 10});
    auto test = terrain1->getModelMatrix();
    config = {.shape=config.Mesh, .type=config.Static};
    terrain1->setCollider(config);
    scene->addComponent(terrain1);

//    /// todo - first create new Terrain() and then use createFromGeometry or create a better factory.
//    Terrain *terrain1 = new Terrain("test_map_64", 1, 0, 1);
//    config = {.shape=config.HeightMap, .type=config.Static};
//    terrain1->setCollider(config);
//    terrain1->setPosition({0, 0, 0});
//    scene->addComponent(terrain1);

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
    setupScene(engine->currentScene);
    interactionLayer->selectedModel = testSphere;


    /// kick-start the main loop
    engine->start();

    Debug::show("[>] Expected engine->stop()");
}
