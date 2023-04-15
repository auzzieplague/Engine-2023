#pragma once

#include "Layer.h"
#include "../../core/Window.h"
#include "graphics/api/GraphicsAPI.h"

class WindowLayer : public Layer {

public:

//    explicit WindowLayer(GraphicsAPI *m_api);

    void onAttach(Scene *) override ;

    void onDetach(Scene *) override ;

    void processInput(Scene *scene) override ;

    void afterRender(Scene *scene) override ;
};
