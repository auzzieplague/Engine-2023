#include "Scene.h"

void Scene::addModel(Model *model) {
    this->modelsToRender.push_back(model);
    if (model->collider) {
        // do some physics assigment
        this->modelsWithPhysicsQueue.push_back(model);
    }

// this->staticMeshesTree->Insert ..
}

void Scene::addComponent(Component *component) {
    // todo: add spawn queue for threading
    switch (component->getType()) {
        case ObjectType::OT_Model:
            this->addModel(dynamic_cast<Model *>(component));
            break;
        default:
            this->componentList.push_back(component);
            break;
    }
}

Scene::Scene() {
    currentCamera = new Camera();
}
