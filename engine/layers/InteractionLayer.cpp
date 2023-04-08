#pragma once

#include "InteractionLayer.h"

void InteractionLayer::onAttach(Scene *scene)  {
    // bind this input to inputInstance
    std::cout << "[>] Interaction Attached\n";
    this->input = new Input (scene->currentWindow->glRef);
};