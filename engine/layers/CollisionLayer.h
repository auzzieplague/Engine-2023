#pragma once

#include "Layer.h"

/**
 * @author Michael.Whinfrey
 */
class CollisionLayer : public Layer {
public:
    void onAttach(Scene *scene) override;

    void update(Scene *scene) override;

    void render(Scene *scene) override;
};


