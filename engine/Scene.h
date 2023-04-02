#pragma once

#include "Object.h"
#include "components/Components.h"

class Scene: public Object {
    /// at a high level we just want to add components to the scene graph
    std::vector<Component*> componentList;

public:
    void addComponent (Component *);
};

