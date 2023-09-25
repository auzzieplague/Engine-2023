#pragma once

#include <Object.h>
#include <Scene.h>
#include <imgui/imgui.h> // all layers require access to IMGUI for debugging windows

class Layer : public Object {
public:
    GraphicsAPI *api;
    Scene * currentScene = nullptr;

    virtual void setApi(GraphicsAPI *api) {
        this->api = api;
    }

    ObjectType getType() override {
        return ObjectType::OT_Layer;
    };

    // overrides
    bool initialised = false;

    virtual uint32_t getFrequency() { return 1; };

    virtual void init(Scene *) {}

    virtual void onAttach(Scene *) {}

    virtual void onDetach(Scene *) {}

    virtual void beforeUpdate(Scene *) {}

    virtual void update(Scene *) {}

    virtual void afterUpdate(Scene *) {}

    // expects that gui platform is checked through scene and rendered accordingly in derived class
    virtual void appendToGui(Scene *) {}

    virtual void beforeRender(Scene *) {}

    virtual void render(Scene *) {}

    virtual void afterRender(Scene *) {}

    virtual void processInput(Scene *) {}

};

