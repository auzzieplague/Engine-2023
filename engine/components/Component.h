#pragma once
// predefine all components here, rootMesh, m_material, texture, animation, script etc.

#include "../Object.h"
#include "../../core/Transform.h"


class Component : public Object {
protected:
    Transform localTransform{};
    Transform worldTransform{};
    Transform combinedTransform{};
    bool m_dirty = true;
    bool m_ready = false;

public:
    ObjectType getType() override {
        return ObjectType::OT_Component;
    };

    std::vector<Component *> childComponents;
    virtual void addChild(Component *child);

    [[nodiscard]] virtual bool isDirty() const;
    void setDirty(bool dirty = true);
    [[nodiscard]] virtual bool isReady();
    void setReady(bool ready = true);

    virtual void setLocalPosition(glm::vec3 newPosition);
    virtual void setLocalRotation(glm::vec3 newRotation);
    virtual void setLocalRotation(glm::quat rotation);
    virtual void setLocalScale(glm::vec3 newScale);
    virtual void setLocalTransform(Transform transform);

    [[nodiscard]] virtual glm::vec3 getLocalPosition();
    [[nodiscard]] virtual glm::quat getLocalRotation();
    [[nodiscard]] virtual glm::vec3 getLocalScale();
    [[nodiscard]] virtual glm::mat4 getLocalMatrix();
    [[nodiscard]] virtual Transform getLocalTransform() const;

    virtual void setWorldPosition(glm::vec3 newPosition);
    virtual void setWorldRotation(glm::vec3 newRotation);
    virtual void setWorldRotation(glm::quat rotation);
    [[nodiscard]] virtual glm::vec3 getWorldPosition();
    [[nodiscard]] virtual glm::quat getWorldRotation();
    [[nodiscard]] virtual Transform getWorldTransform() const;
    [[nodiscard]] virtual glm::mat4 getTransformMatrix();
    virtual void setWorldTransform(Transform transform);

    virtual void updateChildTransforms();
    virtual void updateCombinedTransform();



    virtual void rotateX(float degrees);
    virtual void rotateY(float degrees);
    virtual void rotateZ(float degrees);

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
     * update the game object's position, rotation, and scale based on any changes in the game world or user input
     */
    virtual void update() {
        std::cout << "update not implemented for component\n";
    };
};