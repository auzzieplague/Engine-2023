#pragma once
// predefine all components here, rootMesh, m_material, texture, animation, script etc.

#include "../Object.h"
#include "../../core/Transform.h"


class Component : public Object {
protected:
    Transform m_transform{};
    Transform worldTransform; // to be updated when parents transform
    bool m_dirty = true;
    bool m_ready = false;

public:
    [[nodiscard]] virtual bool isDirty() const;

    void setDirty(bool dirty = true);

    [[nodiscard]] virtual bool isReady();

    void setReady(bool ready = true);

    virtual bool makeReady() { return false; };

    [[nodiscard]] Transform getTransform() const;

    std::vector<Component *> childComponents;

    virtual void setPosition(glm::vec3 newPosition);

    virtual void setScale(glm::vec3 newScale);

    virtual void setRotation(glm::vec3 newRotation);

    [[nodiscard]] virtual glm::vec3 getPosition();

    [[nodiscard]] virtual glm::vec3 getScale();

    [[nodiscard]] virtual glm::quat getRotation();

    [[nodiscard]] virtual glm::mat4 getMatrix();

    ObjectType getType() override {
        return ObjectType::OT_Component;
    };


    /**
     *  create a game object that represents the 3D model in the game world.
     *  The game object should contain the rootMesh and m_material objects,
     *  as well as any other relevant information such as the object's m_position, m_rotation, and scale.
     */
    virtual void init() {
        std::cout << "render not implemented for component\n";
    }

    /**
     *  render the game object using the engine's rendering pipeline.
     *  This may involve setting m_up the camera, setting shader parameters, and sending the rootMesh data to the GPU.
     */
    virtual void render() {
        std::cout << "render not implemented for component\n";
    };

    /**
     * update the game object's m_position, m_rotation, and scale based on any changes in the game world or user input.
     */
    virtual void update() {
        std::cout << "update not implemented for component\n";
    };


};

