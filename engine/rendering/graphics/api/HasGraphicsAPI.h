#pragma once

#include "GraphicsBehaviour.h"

// trait with setter and properties for graphics API
class HasGraphicsAPI {
protected:
    static GraphicsAPI *graphicsApi;

    GraphicsBehaviour *api;

    void setGraphicsAPI(GraphicsAPI *api);
};
