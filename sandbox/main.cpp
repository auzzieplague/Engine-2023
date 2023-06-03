#include <iostream>
#include "../engine/Engine.h"
#include "../engine/layers/CollisionLayer.h"
#include "../engine/layers/PhysicsLayer.h"

Model *playerObject;

void setupScene(Scene *scene) {

    auto *lightPos = new Model();
    lightPos = Model::createFromGeometry(Geometry::ShapeType::Cube,GeometryConfig{.sphere{.radius=0.5, .rings=10, .sectors=10}});
    lightPos->setPosition({0, 2, -1});
    scene->addComponent(lightPos);

    playerObject = Model::createFromGeometry(Geometry::ShapeType::Cube,
//                                           GeometryConfig{.sphere{.radius=0.5, .rings=10, .sectors=10}}
                                           GeometryConfig{.box{.sizeX=2,.sizeY=2,.sizeZ=2}}
                                           );

    Material material;
    material.setAmbientColor(glm::vec3(0,1,0));
    material.loadFromAsset("mats_ground", "grass1");
    // load texture - done
    // add material - done
    // setMaterial on mesh - done
    // push material textures to shader
    // update shader to use textures


    playerObject->setScale({1, 1, 1 });
    playerObject->setMaterial(material);
    playerObject->setPosition({0, 0, 0});

    ColliderConfig config{};
//    config.shape = config.Box;
//    config.type = config.Static;
//    playerObject->setCollider(config);
    scene->addComponent(playerObject);

//    return;

    auto *terrain1 = new Model();
    terrain1->getMeshFromHeightMap("test_map_64");
    terrain1->setPosition({0, -20, 0});
    terrain1->setRotation({0, 0, 0});
    terrain1->setScale({100, 10, 100});
    terrain1->setMaterial(material);
    auto test = terrain1->getModelMatrix();
    config = {.shape=config.Mesh, .type=config.Static};
    terrain1->setCollider(config);
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
