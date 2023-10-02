#include "GraphicsLayer.h"

void GraphicsLayer::onAttach(Scene *) {
    {
        Debug::show("[>] Graphics Attached");
        api->initialise();
        api->queryCapabilities();
//        api->displayCapabilities();
        api->demoTriangle();
    };
}