
#include <Engine.h>
#include <API_OpenGL.h>
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

    engine->attachLayer(new WindowLayer());    // maintains the window interface & required for input processing
    engine->attachLayer(new GraphicsLayer());  // uses the specified Graphics API to render the scene

    /// kick-start the main loop
    engine->start();

    Debug::show("[>] Expected engine->stop()");
}
