#pragma once
// prefine all components here, mesh, material, texture, animation, script etc.

#include "../Object.h"
#include "../../core/Transform.h"


class Component : public Object {
    std::vector<Component *> childComponents;
    // has child component list and then underlying mechanics reference the components in the list
    // should have a scene components list and everything can just references the instances of components as required - mayeb
public:

    ObjectType getType() override {
        return ObjectType::OT_Component;
    };

    Transform transform;
    bool isDirty = true;
    bool isReady = false;

    virtual bool readyCheck(){
        return isReady;
    };

    /**
     *  create a game object that represents the 3D model in the game world.
     *  The game object should contain the mesh and material objects,
     *  as well as any other relevant information such as the object's position, rotation, and scale.
     */
    virtual void init() {
        std::cout << "render not implemented for component\n";
    }

    /**
     *  render the game object using the engine's rendering pipeline.
     *  This may involve setting up the camera, setting shader parameters, and sending the mesh data to the GPU.
     */
    virtual void render() {
        std::cout << "render not implemented for component\n";
    };

    /**
     * update the game object's position, rotation, and scale based on any changes in the game world or user input.
     */
    virtual void update() {
        std::cout << "update not implemented for component\n";
    };
};

