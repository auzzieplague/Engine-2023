#pragma once

#include "../../core/Window.h"
#include "Layer.h"
#include "../components/Geometry.h"
#include "graphics/api/RenderingConfig.h"
#include "graphics/GraphicsFlag.h"

class GraphicsLayer2 : public Layer {

public:
    std::string getName() override{
        return "Graphics Layer 2";
    };

    void setApi(GraphicsAPI *api) override {
        this->api = api;
        // let any graphics objects that contain their own setup methods know which API to call.
        Mesh::setApi(api);
        Terrain::setApi(api);
    };

    void onAttach(Scene *) override {
        Debug::show("[>] Graphics Attached");
        api->initialise();
        api->setCapabilities();
        api->displayCapabilities();
    };

    void render(Scene *) override {

    };

    void update(Scene *) override {

    };
};
