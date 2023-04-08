#pragma once

#include "Object.h"
#include "components/Components.h"
#include "components/Camera.h"
#include "../core/Window.h"

class Scene: public Object {
    /// at a high level we just want to add components to the scene graph
    std::vector<Component*> componentList;
public:

    Scene();

    void addComponent (Component *);

    Camera *currentCamera;
    Window *currentWindow;
};

