#include "Scene.h"

void Scene::addModel(Model *model) {
    // todo: need to insert the models into the render array at the right spot
    // keep pointers to the last BASE, DIFFUSE, NORMAL items to be rendered
    // might have to change vector to dequeue or something
    auto shaderType = model->mRootMesh->getMaterial().getShaderType();

    this->modelsInScene.push_back(model);
    if (model->mCollider) {
        // do some physics assigment
        this->modelsWithPhysicsQueue.push_back(model);
    }
}


void Scene::addComponent(Component *component) {
    // todo: add spawn queue for threading
    switch (component->getType()) {
        case ObjectType::OT_Model:
        case ObjectType::OT_Terrain: // terrains now using meshes
            this->addModel(dynamic_cast<Model *>(component));
            break;
        default:
            break;
    }
    this->componentList.push_back(component);
}

Scene::Scene() {
    currentCamera = new Camera();
}


