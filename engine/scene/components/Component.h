#pragma once
// predefine all components here, mRootMesh, m_material, texture, animation, script etc.

#include <Object.h>
#include <Transform.h>

class IMGuiLayer;       // forward declare friend class
class InteractionLayer; // forward declare friend class

class Component : public Object {
    friend class IMGuiLayer;

    friend class InteractionLayer;

protected:
    bool mDirty = true;
    bool mReady = false;
    bool mPaused = false;
    std::string filePath;
    std::string fileName;

    // for editor direct access - might be able to friend class / protected access these
    Transform localTransform{};
    Transform worldTransform{};

public:
    bool renderLast = false;
    Component *parentComponent = nullptr;
    Component *rootComponent = nullptr;
    std::vector<Component *> childComponents;

    bool selectable = false;
    bool highlighted = false;
    bool selected = false;
    bool dynamic = false;

    void setRenderLast(bool last = true);

    void setSelectable(bool selectable = true);

    [[nodiscard]] const std::string &getFilePath() const;

    [[nodiscard]] const std::string &getFileName() const;

    std::string getIdentifier() {
        return this->getName() + std::to_string(this->objectID);
    }

    Component() {
        this->rootComponent = this;
    };

    ObjectType getType() override {
        return ObjectType::OT_Component;
    };

    void setFilePath(const std::string &fullPath);


    virtual void addChild(Component *child);

    [[nodiscard]] virtual bool isDirty() const;

    void setDirty(bool dirty = true);

    [[nodiscard]] virtual bool isReady();

    void setReady(bool ready = true);

    /**
     * Transform hook, to be overridden in child classes such as Model, where
     * additional functionality needs to be implemented
     */
    virtual void onTransformChange() {};

    virtual void pause() { this->mPaused = true; };

    virtual bool isPaused() { return this->mPaused; };

    virtual void resume() { this->mPaused = false; };

    virtual void setPosition(glm::vec3 newPosition);

    virtual void setLocalRotation(glm::vec3 newRotation);

    virtual void setLocalRotation(glm::quat rotation);

    virtual void setLocalScale(glm::vec3 newScale);

    virtual void setLocalScale(float newScale);

    virtual void autoScale();

    virtual void setLocalTransform(Transform transform);

    [[nodiscard]] virtual glm::vec3 getLocalPosition();

    [[nodiscard]] virtual glm::quat getLocalRotation();

    [[nodiscard]] virtual glm::vec3 getLocalScale();

    [[nodiscard]] virtual glm::mat4 getLocalMatrix();

    [[nodiscard]] virtual glm::mat4 getWorldMatrix();

    [[nodiscard]] virtual Transform getWorldTransform() const;

    virtual void rotateX(float degrees);

    virtual void rotateY(float degrees);

    virtual void rotateZ(float degrees);

    virtual void roll(float degrees);

    virtual void pitch(float degrees);

    virtual void yaw(float degrees);

    void rotate(glm::vec3 newRotation);

    void move(glm::vec3 offset);

    void moveForward(float amount) {};

    void scale(glm::vec3 scale);

    void scale(float scale);

    /**
     *  create a game object that represents the 3D model in the game world.
     *  The game object should contain the mRootMesh and m_material objects,
     *  as well as any other relevant information such as the object's mPosition, mRotation, and scale.
     */
    virtual void init() {
        Debug::error("render not implemented for component\n");
    }

    /**
     *  render the game object using the engine's rendering pipeline.
     *  This may involve setting m_up the camera, setting shader parameters, and sending the mRootMesh data to the GPU.
     */
    virtual void render() {
        Debug::error("render not implemented for component\n");
    };

    /**
     * update the game object's position, rotation, and scale based on any changes in the game world or user input
     */
    virtual void update() {
        Debug::error("update not implemented for component\n");
    };

};