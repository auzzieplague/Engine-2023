#pragma once

#include "Object.h"
#include "components/Camera.h"
#include "../core/Window.h"
#include "components/Model.h"

class Scene : public Object {
    /// at a high level we just want to add components to the scene graph
public:
    float currentFrameRate = 1.0f;
    std::vector<Component *> componentList;
    std::vector<Model *> modelsToRender;

    Scene();

    void addComponent(Component *);

    Camera *currentCamera;
    Window *currentWindow;
};

