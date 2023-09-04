#pragma once

#include "Layer.h"
#include "Window.h"
#include "graphics/api/GraphicsAPI.h"

class WindowLayer : public Layer {

public:
    std::string getName() override{
        return "Window Layer";
    };

    void onAttach(Scene *) override;

    void onDetach(Scene *) override;

    void processInput(Scene *scene) override;

    void afterRender(Scene *scene) override;
};
