
#include <Engine.h>
#include <API_OpenGL.h>
#include <API_DirectX.h>

#include <API_Vulkan.h>

#include <WindowLayer.h>

void outputExecutionMode() {
#ifdef _WIN64
    std::cout << "Running in 64-bit mode" << std::endl;
#else
    std::cout << "Running in 32-bit mode" << std::endl;
#endif
}

int main() {

    /// Required Layers
    Engine *engine = Engine::getInstance();
    engine->setGraphicsApi(new API_OpenGL());

//    engine->setGraphicsApi(new API_DirectX());
//    engine->setGraphicsApi(new API_OpenGL(`));
//    engine->setGraphicsApi(new API_Vulkan()); // needs breaking down into smaller initialisation

    engine->attachLayer(new WindowLayer());    // maintains the window interface & required for input processing
    engine->attachLayer(new GraphicsLayer());  // uses the specified Graphics API to render the scene

    try {
        Debug::show("[>] engine->start()");
        engine->start();
    } catch (std::exception exception) {
        Debug::show("[!] error encountered shutting down safely");
    }

    Debug::show("[>] engine->stop()");
    engine->stop();


}
