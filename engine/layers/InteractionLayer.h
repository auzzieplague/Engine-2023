#pragma once

#include "Layer.h"
#include "../../core/Input.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "../components/IMGuiComponents.h"


class InteractionLayer : public Layer {
private:

    unsigned int iconAtlas;

    enum UserInteractionMode {
        UI_PLAY,
        UI_EDIT
    };
    static unsigned int InteractionMode;
    Input *input;

public:
    Component *currentComponent = nullptr;

    void onAttach(Scene *scene) override;
    void appendToGui(Scene *scene) override;

    void processInput(Scene *scene) override;

    void processCameraInput(Scene *scene, float movement);

    void handleCharacterKeysWithPhysics();

    void handleCharacterKeys(float movement);

    void selectedComponentGui(Component *);

    void transformGui(std::string text, Transform transform);

    void sceneComponentsGui(Scene *scene);

    void toolboxGui(Scene *scene);

    void componentTreeGui(Component *component);

    void assetsDirectoryGui();
};


