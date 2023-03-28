//
// Created by auzzi on 24/03/2023.
//

#ifndef COMPONENTLAYOUT_SCENE_H
#define COMPONENTLAYOUT_SCENE_H


#include "Object.h"
#include "components/Component.h"

class Scene: Object {
    std::vector<Component*> entities;
    std::vector<Component*> lights;
    std::vector<Component*> terrains;
    std::vector<Component*> geometry;
    Component *octree;
};


#endif //COMPONENTLAYOUT_SCENE_H
