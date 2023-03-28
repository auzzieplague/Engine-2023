

#ifndef COMPONENTLAYOUT_COMPONENT_H
#define COMPONENTLAYOUT_COMPONENT_H

// prefine all components here, mesh, material, texture, animation, script etc.

#include "../Object.h"

class Component;
class Mesh;
class Material;
class Texture;
class Animation;


class Component: Object {
    std::vector<Component *> Components;
    // has component list and then underlying mechanics reference the components in the list
    // should have  ascene components list and everything can just references the instances of components as required - mayeb
};


#endif //COMPONENTLAYOUT_COMPONENT_H
