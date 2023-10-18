#include "HasGraphicsAPI.h"

GraphicsAPI *HasGraphicsAPI::graphicsApi = nullptr;


void HasGraphicsAPI::setGraphicsAPI(GraphicsAPI *api) {
    {
        graphicsApi = api;
    }
}
