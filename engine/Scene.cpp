#include "Scene.h"

void Scene::addModel(Model *model) {
    this->modelsToRender.push_back(model);
    if (model->mCollider) {
        // do some physics assigment
        this->modelsWithPhysicsQueue.push_back(model);
    }

// this->staticMeshesTree->Insert ..
}

void Scene::addTerrain(Terrain *terrain) {
    this->terrainsToRender.push_back(terrain);
    if (terrain->mCollider) {
        // do some physics assigment
        this->terrainsWithPhysicsQueue.push_back(terrain);
    }
}

void Scene::addComponent(Component *component) {
    // todo: add spawn queue for threading
    switch (component->getType()) {
        case ObjectType::OT_Model:
            this->addModel(dynamic_cast<Model *>(component));
            break;
        case ObjectType::OT_Terrain:
            this->addTerrain(dynamic_cast<Terrain *>(component));
            break;
        default:
            this->componentList.push_back(component);
            break;
    }
}

Scene::Scene() {
    currentCamera = new Camera();
}


