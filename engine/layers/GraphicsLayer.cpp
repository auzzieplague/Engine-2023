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
    api->setCapabilities();
    api->displayCapabilities();
}

void GraphicsLayer::meshRenderConfig(Scene *scene) {

    singleRenderConfig.shaderID = api->loadShader("general.vert", "general.frag");
    singleRenderConfig.enable(api->getFlag((CULL_FACE)));
    singleRenderConfig.enable(api->getFlag((DEPTH_TEST)));
    singleRenderConfig.setClearFlag(api->getFlag((CLEAR_COLOUR_BUFFER)));
    singleRenderConfig.setClearFlag(api->getFlag((CLEAR_DEPTH_BUFFER)));

    api->beginRender(singleRenderConfig);
    api->shaderSetProjection(scene->currentCamera->getProjectionMatrix());
    api->shaderSetView(scene->currentCamera->getViewMatrix());

    instanceRenderConfig.shaderID = api->loadShader("generalInstanced.vert", "general.frag");
    instanceRenderConfig.enable(api->getFlag((CULL_FACE)));
    instanceRenderConfig.enable(api->getFlag((DEPTH_TEST)));
    api->beginRender(instanceRenderConfig);
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
    for (auto meshGroup: this->currentScene->instancedMeshesToRender) {
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

void GraphicsLayer::update(Scene *scene) {
    // pickup and exchange any modelsInSceneQueue that are ready
    scene->instancedMeshesToRender.clear();
    scene->singleMeshesToRender.clear();
    scene->deferredMeshes.clear();

    for (auto model: scene->modelsInScene) {
        for (auto mesh: model->mRootMesh->meshTree) {
//            scene->instancedMeshesToRender[mesh->getID()].push_back(mesh);
            scene->singleMeshesToRender.push_back(mesh);
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

// todo sort meshes into single and instanced renders - because we need to switch shaders

    int currentVID = 0;
    int meshCount = 0;
    Mesh *lastMesh = nullptr;
    std::vector<glm::mat4> transforms;

    api->beginRender(singleRenderConfig);
    api->shaderSetView(scene->currentCamera->getViewMatrix());

    for (auto mesh: scene->singleMeshesToRender) {
        if (!checkDeferMesh(mesh)){
            this->renderSingleMesh(mesh);
        }
    }

//    api->beginRender(instanceRenderConfig);
//    api->shaderSetView(scene->currentCamera->getViewMatrix());

//    for (auto meshGroup: scene->instancedMeshesToRender) {
//        currentVID = meshGroup.first;
//        meshCount = meshGroup.second.size();
//
//        for(const auto mesh : meshGroup.second) {
//            // defer selected model and its sub meshes until after the ZBuffer depth has been read for mouse
//            if (currentScene->selectedComponent && scene->selectedComponent->rootComponent == mesh->rootComponent) {
//                scene->deferredMeshes.push_back(mesh);
//                continue;
//            }
//
//            if (meshCount == 1) {
//                // render these later - using different shader
//                scene->singleMeshesToRender.push_back(mesh);
//                break; // need to
////                this->renderMeshComponent(mesh);
//            } else {
//
//                transforms.push_back(mesh->getWorldMatrix());
//                // should also send / materials - tbc
//            }
//
//            lastMesh = mesh;
//        }
//
//        if (meshCount>1) {
//            this->renderInstancedMesh(lastMesh,transforms);
//        }
//    }

    // todo : mark skymesh and terrains for deffered rendering to increase performance

//    // update mouse depth if required (not every frame - too expensive)
////    if (currentScene->updateMouseFromBuffers) {
//        api->readDepthBuffer(&scene->mouseInZBufferDepth, Input::m_mousePos.x,
//                             scene->currentWindow->height - Input::m_mousePos.y, 1, 1);
////        currentScene->updateMouseFromBuffers = false;
////    }
//    // render any deferred meshes
//    for (auto mesh: scene->deferredMeshes) {
//        this->renderSingleMesh(mesh);
//    }
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

    api->shaderSetTransformList(transforms);
    api->shaderSetMaterial(mesh->getMaterial());
    api->renderMesh(mesh, transforms.size());
}

void GraphicsLayer::checkDirtyCamera(Scene *scene) const {
    if (scene->currentCamera->isDirty()) {
        api->shaderSetMat4("view", scene->currentCamera->getViewMatrix());
        scene->currentCamera->setDirty(false);
    }
}

