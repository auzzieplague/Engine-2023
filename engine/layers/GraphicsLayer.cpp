#include "GraphicsLayer.h"
#include "graphics/api/GraphicsAPI.h"

void GraphicsLayer::setApi(GraphicsAPI *api) {
    this->api = api;
    Mesh::setApi(api);
}

void GraphicsLayer::onAttach(Scene *scene) {
    Debug::show("[>] Graphics Attached");
    initialRenderingSetup(scene);
}

void GraphicsLayer::initialRenderingSetup(Scene *scene) {
    meshConfig.shaderID = api->loadShader("general.vert", "general.frag");
    meshConfig.disable(flag(CULL_FACE));
    meshConfig.enable(flag(DEPTH_TEST));
    meshConfig.setClearFlag(flag(CLEAR_COLOUR_BUFFER));
    meshConfig.setClearFlag(flag(CLEAR_DEPTH_BUFFER));

//    meshConfig.debugMode=true;
    api->updateRendererConfig(meshConfig);
    api->shaderSetProjection(scene->currentCamera->getProjectionMatrix());
    api->shaderSetView(scene->currentCamera->getViewMatrix());
}

void GraphicsLayer::render(Scene *scene) {
    // update shaders and set m_api properties
    api->updateRendererConfig(meshConfig);
    // camera might be dirty
    checkDirtyCamera(scene);

    for (auto model: scene->modelsToRender) {
        api->shaderSetTransform(model->transform.getModelMatrix());

        // todo model can have many meshes
        api->shaderSetMaterial(model->mesh->material);
        api->renderMesh(model->mesh);

    }
}

void GraphicsLayer::checkDirtyCamera(Scene *scene) const {
    if (scene->currentCamera->isDirty) {
        api->shaderSetMat4("view", scene->currentCamera->getViewMatrix());
        scene->currentCamera->isDirty = false;
    }
}

unsigned int GraphicsLayer::flag(GraphicsFlag graphicsFlag) {
    // grab mapping from m_api for our enumerations
    return api->getFlag(graphicsFlag);
}
