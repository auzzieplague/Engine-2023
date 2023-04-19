//
// Created by auzzi on 24/03/2023.
//

#include "Scene.h"

void Scene::addComponent(Component * component) {
    // todo: add spawn queue for threading
    switch (component->getType()) {
        case ObjectType::OT_Model:
            this->modelsToRender.push_back(dynamic_cast<Model *>(component));
            break;
        default:
            this->componentList.push_back(component);
    }

    // todo add octree to scene
    // add component reference and bounding sphere into octree
    Debug::show("component added");
}

Scene::Scene() {
    currentCamera = new Camera();
}
