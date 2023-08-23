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

/**
 * this method renders the objectID to the shader and sets the MouseOver object ID
 * @param meshes
 */
void GraphicsLayer::updateMouseOverObject() {

    // note here we are only interested in objects that are selectable however, we still need to render
    // things that aren't selectable to obscure objects correctly from view
    // object picking from meshesToRender using physx will probably be a lot more affective
    api->beginRender(objectTrackerConfig);
    api->shaderSetView(currentScene->currentCamera->getViewMatrix());
    int currentVID = 0;
    for (auto meshGroup: this->currentScene->meshesToRender) {
        //todo, can also benefit from instanced rendering
        currentVID = meshGroup.first;
        for (const auto mesh: meshGroup.second) {

            if (currentScene->selectCurrentMouseTarget && mesh->objectID == currentScene->mouseOverObjectID) {
                currentScene->selectComponent(mesh);
            }

            api->shaderSetTransform(mesh->getWorldMatrix());
            api->shaderSetVec3("entityID", mesh->colourID);
            api->renderMesh(mesh);
        }
    }

    api->flushBuffers();
    unsigned char data[4];
    api->readColourBufferRBGA(data, Input::m_mousePos.x,
                              this->currentScene->currentWindow->height - Input::m_mousePos.y, 1, 1);

    currentScene->mouseOverObjectID = data[0] + data[1] * 256 + data[2] * 256 * 256;
}

void GraphicsLayer::render(Scene *scene) {
    std::vector<Mesh *> deferredMeshes;

    // update mouse hover objectID if required (not every frame - too expensive)W
    if (currentScene->updateMouseFromBuffers) {
        // note: only selectedObjects will be highlighted
        this->updateMouseOverObject();
    }


    int currentVID = 0;
    // render the meshes
    api->beginRender(renderConfig);
    api->shaderSetView(scene->currentCamera->getViewMatrix());
    for (auto meshGroup: scene->meshesToRender) {
        currentVID = meshGroup.first;
        for(const auto mesh : meshGroup.second) {

        // defer selected model and its sub meshes until after the ZBuffer depth has been read for mouse
        if (currentScene->selectedComponent && scene->selectedComponent->rootComponent == mesh->rootComponent) {
            deferredMeshes.push_back(mesh);
            continue;
        }

        this->renderMeshComponent(mesh);
        }
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

void GraphicsLayer::update(Scene *scene) {
    // pickup and exchange any modelsInSceneQueue that are ready
    scene->meshesToRender.clear();
    for (auto model: scene->modelsInScene) {
        for (auto mesh: model->mRootMesh->meshTree) {
            scene->meshesToRender[mesh->getID()].push_back(mesh);
        }
    }

}
