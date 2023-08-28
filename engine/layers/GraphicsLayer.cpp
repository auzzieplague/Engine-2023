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
    api->initialise();
    api->setCapabilities();
    api->displayCapabilities();
    meshRenderConfig(scene);
    objectTrackerRenderConfig(scene);
    Material::initialise();
}

void GraphicsLayer::meshRenderConfig(Scene *scene) {
    singleRenderConfig = api->loadShader("general.vert", "general.frag");
    singleRenderConfig.enable(api->getFlag((CULL_FACE)));
    singleRenderConfig.enable(api->getFlag((DEPTH_TEST)));
    api->initialiseShader(singleRenderConfig);
    // todo - move projection and camera into config -
    api->shaderSetProjection(scene->currentCamera->getProjectionMatrix());
    api->shaderSetView(scene->currentCamera->getViewMatrix());

    // todo loadShader should return a shader config object

    instanceRenderConfig = api->loadShader("generalInstanced.vert", "generalInstanced.frag");
    instanceRenderConfig.enable(api->getFlag((CULL_FACE)));
    instanceRenderConfig.enable(api->getFlag((DEPTH_TEST)));
    instanceRenderConfig.setClearFlag(api->getFlag((CLEAR_COLOUR_BUFFER)));
    instanceRenderConfig.setClearFlag(api->getFlag((CLEAR_DEPTH_BUFFER)));
    api->initialiseShader(instanceRenderConfig);
    api->shaderSetProjection(scene->currentCamera->getProjectionMatrix());
    api->shaderSetView(scene->currentCamera->getViewMatrix());
}


void GraphicsLayer::objectTrackerRenderConfig(Scene *scene) {
    objectTrackerConfig= api->loadShader("general.vert", "object_lookup.frag");
    objectTrackerConfig.setClearFlag(api->getFlag((CLEAR_COLOUR_BUFFER)));
    objectTrackerConfig.setClearFlag(api->getFlag((CLEAR_DEPTH_BUFFER)));
    objectTrackerConfig.clearColour = {0, 0, 0, 1};
    api->initialiseShader(objectTrackerConfig);
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

    // we might also store the id in the vertexbufferattribute

    api->beginRender(objectTrackerConfig);
    api->shaderSetView(currentScene->currentCamera->getViewMatrix());
    int currentVID = 0;

    // todo selection
    for (auto mesh: this->currentScene->singleMeshesToRender) {
//    for (auto meshGroup: this->currentScene->instanceMeshes) {
        //todo, can also benefit from instanced rendering
//        currentVID = meshGroup.first;
//        for (const auto mesh: meshGroup.second) {

        if (currentScene->selectCurrentMouseTarget && mesh->objectID == currentScene->mouseOverObjectID) {
            currentScene->selectComponent(mesh);
        }

        api->shaderSetTransform(mesh->getWorldMatrix());
        api->shaderSetVec3("entityID", mesh->colourID);
        api->renderMesh(mesh);
//        }
    }

    api->flushBuffers();
    unsigned char data[4];
    api->readColourBufferRBGA(data, Input::m_mousePos.x,
                              this->currentScene->currentWindow->height - Input::m_mousePos.y, 1, 1);

    currentScene->mouseOverObjectID = data[0] + data[1] * 256 + data[2] * 256 * 256;
}

void GraphicsLayer::update(Scene *scene) {
    // pickup and exchange any modelsInSceneQueue that are ready
    scene->instancedMeshesToRender.clear();
    scene->singleMeshesToRender.clear();
    scene->deferredMeshes.clear();

    for (auto model: scene->modelsInScene) {
        if (model->mRootMesh->meshTree.size() > 1) {
            for (auto mesh: model->mRootMesh->meshTree) {
                // usually we initialise if not ready inside the rendered but here we need those vIDs
                auto meshID = mesh->getID();
                if (meshID != 0) {
                    scene->instancedMeshesToRender[meshID].push_back(mesh);
                } else {
                    mesh->generateMeshID();
                }

//                scene->singleMeshesToRender.push_back(mesh);
            }
        } else {
            scene->singleMeshesToRender.push_back(model->mRootMesh);
        }
    }
}

bool GraphicsLayer::checkDeferMesh(Mesh *mesh) {
    if (mesh->renderLast ||
        (currentScene->selectedComponent
         && currentScene->selectedComponent->rootComponent == mesh->rootComponent)) {
        currentScene->deferredMeshes.push_back(mesh);
        return true;
    }
    return false;
}

void GraphicsLayer::render(Scene *scene) {
    // update mouse hover objectID if required (not every frame - too expensive)W
    if (currentScene->updateMouseFromBuffers) {
        // note: only selectedObjects will be highlighted
        this->updateMouseOverObject();
    }

    Mesh *renderMesh = nullptr;
    std::vector<glm::mat4> transforms;

    api->beginRender(instanceRenderConfig);
    api->shaderSetView(scene->currentCamera->getViewMatrix());

    for (const auto& meshGroup: scene->instancedMeshesToRender) {
        transforms.clear();
        for(const auto mesh : meshGroup.second) {
            if (checkDeferMesh(mesh)) {
                continue;
            }
            transforms.push_back(mesh->getWorldMatrix());
            if (renderMesh == nullptr) {
                renderMesh = mesh;
            }

            this->renderInstancedMesh(renderMesh,transforms);
        }

        renderMesh = nullptr;
    }

    api->beginRender(singleRenderConfig);
    api->shaderSetView(scene->currentCamera->getViewMatrix());

    for (auto mesh: scene->singleMeshesToRender) {
        if (!checkDeferMesh(mesh)) {
            this->renderSingleMesh(mesh);
        }
    }
    // todo : mark sky mesh and terrains for deferred rendering to increase performance

//    // update mouse depth if required (not every frame - too expensive)
////    if (currentScene->updateMouseFromBuffers) {
//        api->readDepthBuffer(&scene->mouseInZBufferDepth, Input::m_mousePos.x,
//                             scene->currentWindow->height - Input::m_mousePos.y, 1, 1);
////        currentScene->updateMouseFromBuffers = false;
////    }


    // render any deferred meshes
    for (auto mesh: scene->deferredMeshes) {
        this->renderSingleMesh(mesh);
    }
}

void GraphicsLayer::renderSingleMesh(Mesh *mesh) const {
    glm::vec3 highlight;
    api->shaderSetTransform(mesh->getWorldMatrix());
    highlight = mesh->highlighted ? glm::vec3{2, 2, 2} : glm::vec3{1.0, 1.0, 1.0};
    api->shaderSetVec3("highlight", highlight);
    api->shaderSetMaterial(mesh->getMaterial());
    api->renderMesh(mesh);
}

void GraphicsLayer::renderInstancedMesh(Mesh *mesh, std::vector<glm::mat4> transforms) {
    api->renderInstancedMesh(mesh, transforms);
}

void GraphicsLayer::checkDirtyCamera(Scene *scene) const {
    if (scene->currentCamera->isDirty()) {
        api->shaderSetMat4("view", scene->currentCamera->getViewMatrix());
        scene->currentCamera->setDirty(false);
    }
}

