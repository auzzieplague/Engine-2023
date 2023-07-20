#pragma once

#include "CollisionLayer.h"
#include "graphics/api/GraphicsAPI.h"

void CollisionLayer::onAttach(Scene *scene) {
    updateLayerVariables(scene);
    objectTrackerRenderConfigSetup(scene);
    Debug::show("[>] Collision Attached");
}

void CollisionLayer::updateLayerVariables(Scene *scene) {
    this->mNearPlane = scene->currentCamera->getNearClip();
    this->mFarPlane = scene->currentCamera->getFarClip();
}

void CollisionLayer::processCollisions(Scene *scene) {
    // check mCollider of models
    // will be checking collidable models in the scene for now just checking all render models

    /// just for debugging collision
    bool alreadyColliding[1000];
    for (bool &i: alreadyColliding) {
        i = false;
    }

    int collider1 = 0;
    int collider2 = 1;
    uint max = scene->modelsInScene.size() - 1;
    float colourOffset = 0.15f;
    /*
     * Note: time complexity (n^2 - n) / 2 for these comparisons
     * each iteration compares all the proceeding items against itself
     * that means the current item will have been tested against all previous items already
     * (that is, all previous items have tested themselves against the current item)
     * as we traverse through the list the number of items to be compared will linearly decrease
     * e.g. comparing 10 items [iteration:comparisons] [1:9], [2:8], [3:7], [4:6] ..
     */

    if (Debug::getIteration() == 1) {
        std::cout << "--------- Collision Report ------\n";
    }
    while (collider1 <= max) {

        while (collider2 <= max) {
            // check if models are collidable - will be its own array
            if (scene->modelsInScene[collider1]->mCollider && scene->modelsInScene[collider2]->mCollider) {


                if (scene->modelsInScene[collider1]->mCollider->isColliding(
                        scene->modelsInScene[collider2]->mCollider)) {

                    if (Debug::getIteration() == 1) {
                        std::cout << " [" << collider1 << "-X-" << collider2 << "] ";
                    }

                    scene->modelsInScene[collider1]->mRootMesh->getMaterial().setAmbientColor({colourOffset, 0, 0});
                    colourOffset += 0.1f;

                    scene->modelsInScene[collider2]->mRootMesh->getMaterial().setAmbientColor({colourOffset, 0, 0});
                    colourOffset += 0.1f;

                    alreadyColliding[collider1] = true;
                    alreadyColliding[collider2] = true;

                } else {
                    if (Debug::getIteration() == 1) {
                        std::cout << collider1 << "<->" << collider2 << "  ";
                    }
                    if (!alreadyColliding[collider1]) {
                        scene->modelsInScene[collider1]->mRootMesh->restoreMaterial();
                    }
                    if (!alreadyColliding[collider2]) {
                        scene->modelsInScene[collider2]->mRootMesh->restoreMaterial();
                    }
                }
            }
            collider2++;
        }
        if (Debug::getIteration() == 1) {
            std::cout << "\n";
        }
        collider1++;
        collider2 = collider1 + 1;
    }

    if (Debug::getIteration() < 2) {
        Debug::nextIteration();
    }

    // perform collision detection - isColliding
}

void CollisionLayer::appendToGui(Scene *scene) {

    ImGui::Begin("Collision layer");

    ImGui::Text("screen X: %f", this->mouseInClipSpace.x);
    ImGui::Text("screen Y: %f", this->mouseInClipSpace.y);
    ImGui::Text("Target Distance %f", this->mouseOverDistance);
    ImGui::Text("Mouse World %f,%f,%f", scene->cursorInWorld.x, scene->cursorInWorld.y, scene->cursorInWorld.z);
    ImGui::Text("Cursor over object %i", scene->mouseOverObjectID);
    ImGui::Text("camera X: %f", this->currentScene->currentCamera->mPosition.x);
    ImGui::Text("camera Y: %f", this->currentScene->currentCamera->mPosition.y);
    ImGui::Text("camera Z: %f", this->currentScene->currentCamera->mPosition.z);

    ImGui::End();
}

void CollisionLayer::objectTrackerRenderConfigSetup(Scene *scene) {

}

void CollisionLayer::updateScreenRay(Scene *scene) {
    GLfloat depth;
    glReadPixels(Input::m_mousePos.x, scene->currentWindow->height - Input::m_mousePos.y, 1, 1, GL_DEPTH_COMPONENT,
                 GL_FLOAT,
                 &depth);
    depth = 2.0f * depth - 1.0;

    this->mouseOverDistance =
            2.0f * mNearPlane * mFarPlane / (mFarPlane + mNearPlane - depth * (mFarPlane - mNearPlane));

    this->mouseInClipSpace.x = Input::m_mousePos.x / (scene->currentWindow->width * 0.5) - 1.0f;
    this->mouseInClipSpace.y = 1.0f - Input::m_mousePos.y / (scene->currentWindow->height * 0.5) ;

    glm::vec4 ray_clip(this->mouseInClipSpace.x, this->mouseInClipSpace.y, -1.0, 1.0);
    glm::vec4 ray_eye =
            inverse(this->currentScene->currentCamera->mProjectionMatrix) *
            ray_clip; //todo create inverse matrix with projection matrix
    ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);
    glm::vec4 ray_direction = inverse(this->currentScene->currentCamera->mViewMatrix) * ray_eye;
    ray_direction = glm::normalize(ray_direction);

    glm::vec3 rayEndPosition = ray_direction * mouseOverDistance;
    scene->cursorInWorld = this->currentScene->currentCamera->mPosition + rayEndPosition;
//    scene->cursorInWorld+=glm::vec3{1,1,1};
}

void CollisionLayer::afterRender(Scene *scene) {
    updateScreenRay(scene);
}

void CollisionLayer::update(Scene *scene) {
    // todo this mesh list and graphics layer one, should be maintained on scene
    std::vector<Mesh *> meshes;
    for (auto model: scene->modelsInScene) {
        meshes.insert(meshes.end(), model->mRootMesh->meshTree.begin(), model->mRootMesh->meshTree.end());
    }

    for (auto mesh: meshes) {
        mesh->highlighted = mesh->selectable && mesh->objectID == scene->mouseOverObjectID;
    }
}


