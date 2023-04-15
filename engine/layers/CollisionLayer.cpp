#pragma once

#include "CollisionLayer.h"

void CollisionLayer::onAttach(Scene *scene) {
    Debug::show("[>] Collision Attached");
}

void CollisionLayer::update(Scene *scene) {
    // check collider of models
    // will be checking collidable models in the scene for now just checking all render models

    int collider1 = 0;
    int collider2 = 1;
    int max = scene->modelsToRender.size() - 1;

    /*
     * Note: time complexity (n^2 - n) / 2 for these comparisons
     * each iteration compares all the proceeding items against itself
     * that means the current item will have been tested against all previous items already
     * (that is, all previous items have tested themselves against the current item)
     * as we traverse through the list the number of items to be compared will linearly decrease
     * e.g. comparing 10 items [iteration:comparisons] [1:9], [2:8], [3:7], [4:6] ..
     */
    while (collider1 <= max) {

        while (collider2 <= max) {
            // check if models are collidable - will be its own array
            if (scene->modelsToRender[collider1]->collider && scene->modelsToRender[collider2]->collider) {

                if (scene->modelsToRender[collider1]->collider->isColliding(
                        scene->modelsToRender[collider2]->collider)) {
                    scene->modelsToRender[collider1]->mesh->material.setAmbientColor({1.0f, 0, 0});
                    scene->modelsToRender[collider2]->mesh->material.setAmbientColor({1.0f, 0, 0});
                } else {
                    scene->modelsToRender[collider1]->mesh->material.setAmbientColor({1.0f, 1.0f, 1.0f});
                    scene->modelsToRender[collider2]->mesh->material.setAmbientColor({1.0f, 1.0f, 1.0f});
                }

                /// note: in above example, if a node A collides with B but B doesnt collide with C,  C will appear white,
                /// although collision will have been detected ... so dont depend on these colours,
                /// may need flags or something to better identify collisions. works ok with 2 models

            }
            collider2++;
        }

        collider1++;
        collider2 = collider1 + 1;
    }


    // perform collision detection - isColliding
}

void CollisionLayer::render(Scene *scene) {
    // render collision shapes if option enabled

    // set colour red if colliding green if not.

    //if collider m_vertices isn't set initialise it with m_sphere positions.
}


