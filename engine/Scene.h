#pragma once

#include "Object.h"
#include "components/Camera.h"
#include "../core/Window.h"
#include "components/Model.h"
#include "components/colliders/Octree.h"
#include "components/Terrain.h"

class Scene : public Object {
public:
    // todo move these variables to a new class for Editor or Game, theyre not really part of scene
    float currentFrameRate = 1.0f;
    Component *selectedComponent = nullptr;
    unsigned int selectComponentID = 0;
    int mouseOverObjectID;
    bool selectCurrentMouseTarget = false; // helper to select the current mouseOverObjectID as the selected component
    bool moveObjectWithMouse = false;
    glm::vec3 cursorInWorld{};
    float mouseInZBufferDepth = 0;

    physx::PxScene *physicsScene = nullptr; // set on Ini physics on physics layer, accessor for other layers.
    float simulationSpeed = 1.0f / 60.0f;

    std::vector<Component *> componentList;
    std::deque<Model *> modelsInSceneQueue; //todo spawn queue for threading same as onion core
    std::vector<Model *> modelsInScene;

    std::deque<Model *> modelsWithPhysicsQueue;
    std::vector<Model *> modelsWithPhysics;

    Scene();

    void addComponent(Component *);

    void selectComponent(Component *);

    Camera *currentCamera{};
    Window *currentWindow{};

    void addModel(Model *model);

};

