#pragma once

#include "Layer.h"
#include "../../core/Input.h"

class InteractionLayer: public Layer {
private:

    enum UserInteractionMode {
        UI_PLAY,
        UI_EDIT
    };
    static unsigned int InteractionMode;
    Input *input;
public:
    void onAttach(Scene *scene) override;

};


