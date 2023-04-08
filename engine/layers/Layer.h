#pragma once

#include "../Object.h"
#include "../Scene.h"

class Layer: public Object {
public:
    GraphicsAPI *api;

    virtual void setApi(GraphicsAPI *api) {
        this->api = api;
    }

    // overrides
    bool initialised = false;
    virtual uint32_t getType() { return 0; };
    virtual uint32_t getFrequency() { return 0; };
    virtual const char* getName() { return "(missing getName override)"; };

    virtual void onAttach(Scene*) {}
    virtual void onDetach(Scene*) {}

    virtual void beforeUpdate(Scene*) {}
    virtual void update(Scene*) {}
    virtual void afterUpdate(Scene*) {}

    // expects that gui platform is checked through scene and rendered accordingly in derived class
    virtual void appendToGui(Scene*) {}

    virtual void beforeRender(Scene*) {}
    virtual void render(Scene*) {}
    virtual void afterRender(Scene*) {}

    virtual void processInput(Scene*) {}

};

