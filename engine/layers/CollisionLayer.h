#pragma once

#include "Layer.h"
#include "../core/Input.h"
#include "graphics/api/RenderingConfig.h"

/**
 * @author Michael.Whinfrey
 */
class CollisionLayer : public Layer {

    // local layer variables
    float mNearPlane;
    float mFarPlane;
    glm::vec2 mouseInScreenSpace{};
    glm::vec2 mouseInClipSpace{};
    glm::vec3 cursorInWorld{};
    float mouseOverDistance = 0;
//    unsigned int cursorOverObjectID = 0;

public:
    RenderingConfig renderConfig;

    void onAttach(Scene *scene) override;

    void update(Scene *scene) override;

//    void render(Scene *scene) override;
//  todo: fix window properties
// then screenray
    void updateScreenRay(Scene *scene);

    void updateLayerVariables(Scene *scene);

    void appendToGui(Scene *scene) override;

    void processCollisions(Scene *scene);

    void objectTrackerRenderConfigSetup(Scene *scene);

};


