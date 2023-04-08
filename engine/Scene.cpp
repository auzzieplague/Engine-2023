//
// Created by auzzi on 24/03/2023.
//

#include "Scene.h"

void Scene::addComponent(Component * component) {
    // todo: add spawn queue for threading
    this->componentList.push_back(component);

    Debug::show("component added");
}

Scene::Scene() {
    currentCamera = new Camera();
}
