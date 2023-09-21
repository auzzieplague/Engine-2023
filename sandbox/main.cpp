#include <iostream>
#include "../engine/Engine.h"
#include "../engine/layers/CollisionLayer.h"
#include "../engine/layers/PhysicsLayer.h"
#include "../engine/layers/IMGuiLayer.h"
#include "DemoScene.h"
#include "../engine/layers/GraphicsLayer2.h"

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
//    AssetManager::testASSIMP();
//    AssetManager::buildDirectoryStructure("..\\assets");

    /// Required Layers
    Engine *engine = Engine::getInstance();
    engine->setGraphicsApi(new API_DirectX11());

    engine->attachLayer(new WindowLayer());    // maintains the window interface & required for input processing
    /// optional layers
    engine->attachLayer(new GraphicsLayer2());  // uses the specified Graphics API to render the scene
//    engine->attachLayer(new PhysicsLayer());   // uses physx to keep dynamic objects in bounds
//    engine->attachLayer(new CollisionLayer());    // process mouse collisions
//    engine->attachLayer(new IMGuiLayer());

    // setup interaction layer and scene together to inject a tests model
//    auto *interactionLayer = new InteractionLayer();  // editor view
//    engine->attachLayer(interactionLayer);

//    try {
//        setupScene(engine->currentScene);
//    } catch (const std::exception &e) {
//        Debug::show("[!] Scene Setup Error");
//        Debug::show(e.what());
//    }

//    interactionLayer->currentComponent = playerObject;

    /// kick-start the main loop
    engine->start();

    Debug::show("[>] Expected engine->stop()");
}
