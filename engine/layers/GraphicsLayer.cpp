#include "GraphicsLayer.h"
#include "graphics/api/GraphicsAPI.h"
#include "../../core/Input.h"

void GraphicsLayer::setApi(GraphicsAPI *api) {
    this->api = api;
    // let any graphics objects that contain their own setup methods know which API to call.
    Mesh::setApi(api);
    Terrain::setApi(api);
}

void GraphicsLayer::onAttach(Scene *scene) {
    Debug::show("[>] Graphics Attached");
    meshRenderConfig(scene);
    objectTrackerRenderConfig(scene);
    Material::initialise();
}

void GraphicsLayer::meshRenderConfig(Scene *scene) {
    renderConfig.shaderID = api->loadShader("general.vert", "general.frag");
    renderConfig.enable(api->getFlag((CULL_FACE)));
    renderConfig.enable(api->getFlag((DEPTH_TEST)));
    renderConfig.setClearFlag(api->getFlag((CLEAR_COLOUR_BUFFER)));
    renderConfig.setClearFlag(api->getFlag((CLEAR_DEPTH_BUFFER)));

    api->beginRender(renderConfig);
    api->shaderSetProjection(scene->currentCamera->getProjectionMatrix());
    api->shaderSetView(scene->currentCamera->getViewMatrix());
}


void GraphicsLayer::objectTrackerRenderConfig(Scene *scene) {
    objectTrackerConfig.shaderID = api->loadShader("general.vert", "object_lookup.frag");
    objectTrackerConfig.setClearFlag(api->getFlag((CLEAR_COLOUR_BUFFER)));
    objectTrackerConfig.setClearFlag(api->getFlag((CLEAR_DEPTH_BUFFER)));
    objectTrackerConfig.clearColour = {0, 0, 0, 1};
    api->beginRender(objectTrackerConfig);
    api->shaderSetProjection(scene->currentCamera->getProjectionMatrix());
    api->shaderSetView(scene->currentCamera->getViewMatrix());
}

void GraphicsLayer::updateMouseOverObject(std::vector<Mesh *> meshes) {
    api->beginRender(objectTrackerConfig);
    api->shaderSetView(currentScene->currentCamera->getViewMatrix());

    for (auto mesh: meshes) {
        if (currentScene->selectCurrentMouseTarget && mesh->objectID == currentScene->mouseOverObjectID) {
            currentScene->selectComponent(mesh);
        }

        api->shaderSetTransform(mesh->getWorldMatrix());
        api->shaderSetVec3("entityID", mesh->colourID);
        api->renderMesh(mesh);
    }

    api->flushBuffers();
    unsigned char data[4];
    api->readColourBufferRBGA(data, Input::m_mousePos.x,
                              this->currentScene->currentWindow->height - Input::m_mousePos.y, 1, 1);

    currentScene->mouseOverObjectID = data[0] + data[1] * 256 + data[2] * 256 * 256;
}

void GraphicsLayer::render(Scene *scene) {
    std::vector<Mesh *> meshes;
    std::vector<Mesh *> deferredMeshes;
    for (auto model: scene->modelsInScene) {
        meshes.insert(meshes.end(), model->mRootMesh->meshTree.begin(), model->mRootMesh->meshTree.end());
    }

    // update mouse hover objectID if required (not every frame - too expensive)W
//    if (currentScene->updateMouseFromBuffers) {
        this->updateMouseOverObject(meshes);
//    }

    // render the meshes
    api->beginRender(renderConfig);
    api->shaderSetView(scene->currentCamera->getViewMatrix());
    for (auto mesh: meshes) {
        // deffer selected model and its sub meshes until after the ZBuffer depth has been read for mouse
        if (currentScene->selectedComponent && scene->selectedComponent->rootComponent == mesh->rootComponent) {
            deferredMeshes.push_back(mesh);
            continue;
        }

        this->renderMeshComponent(mesh);
    }

    // update mouse depth if required (not every frame - too expensive)
//    if (currentScene->updateMouseFromBuffers) {
        api->readDepthBuffer(&scene->mouseInZBufferDepth, Input::m_mousePos.x,
                             scene->currentWindow->height - Input::m_mousePos.y, 1, 1);
//        currentScene->updateMouseFromBuffers = false;
//    }
    // render any deferred meshes
    for (auto mesh: deferredMeshes) {
        this->renderMeshComponent(mesh);
    }
}

void GraphicsLayer::renderMeshComponent(Mesh *mesh) const {
    glm::vec3 highlight;
    api->shaderSetTransform(mesh->getWorldMatrix());
    highlight = mesh->highlighted ? glm::vec3{2, 2, 2} : glm::vec3{1.0, 1.0, 1.0};
    api->shaderSetVec3("highlight", highlight);
    api->shaderSetMaterial(mesh->getMaterial());
    api->renderMesh(mesh);
}

void GraphicsLayer::checkDirtyCamera(Scene *scene) const {
    if (scene->currentCamera->isDirty()) {
        api->shaderSetMat4("view", scene->currentCamera->getViewMatrix());
        scene->currentCamera->setDirty(false);
    }
}

void GraphicsLayer::update(Scene *) {
    // pickup and exchange any modelsInSceneQueue that are ready

}
