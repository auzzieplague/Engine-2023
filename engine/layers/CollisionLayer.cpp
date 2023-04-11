#pragma once

#include "CollisionLayer.h"

void CollisionLayer::onAttach(Scene *scene) {
    Debug::show("[>] Collision Attached");
}

void CollisionLayer::update(Scene *scene) {
   // perform collision detection - isColliding
}

void CollisionLayer::render(Scene *scene) {
    // render collision shapes if option enabled

    // set colour red if colliding green if not.

    //if collider m_vertices isnt set intialise it with sphere positions.
}


