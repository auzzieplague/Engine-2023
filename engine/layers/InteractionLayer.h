#pragma once

#include "Layer.h"
#include "../../core/Input.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

class InteractionLayer : public Layer {
private:

    enum UserInteractionMode {
        UI_PLAY,
        UI_EDIT
    };
    static unsigned int InteractionMode;
    Input *input;

public:
    Model *selectedModel = nullptr;

    void onAttach(Scene *scene) override;
    void appendToGui(Scene *scene) override;

    void processInput(Scene *scene) override;

    void processCameraInput(Scene *scene, float movement);

    void handleCharacterKeysWithPhysics();

    void handleCharacterKeys(float movement);

    void selectedObjectGui(Scene *scene);
};


