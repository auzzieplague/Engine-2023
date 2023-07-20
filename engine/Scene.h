#pragma once

#include "Object.h"
#include "components/Camera.h"
#include "../core/Window.h"
#include "components/Model.h"
#include "components/colliders/Octree.h"
#include "components/Terrain.h"

class Scene : public Object {
    /// at a high level we just want to add components to the scene graph
public:
    float currentFrameRate = 1.0f;
    Component *selectedComponent = nullptr;
    int mouseOverObjectID;
    bool selectHoveredComponent = false;
    unsigned int selectComponentID = 0;
    glm::vec3 cursorInWorld{};

    physx::PxScene *physicsScene = nullptr; // set on initphysics
    float simulationSpeed = 1.0f / 120.0f;
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

