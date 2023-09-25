#pragma once
#include <GraphicsAPI.h>
#include "../../core/Window.h"
#include "Layer.h"
#include "graphics/GraphicsFlag.h"


class GraphicsLayer : public Layer {

public:
    std::string getName() override{
        return "Graphics Layer";
    };

    void setApi(GraphicsAPI *api) override {
        this->api = api;
        // let any graphics objects that contain their own setup methods know which API to call.
        Mesh::setApi(api);
    };

    void onAttach(Scene *) override ;

    void render(Scene *) override {

    };

    void update(Scene *) override {

    };
};


