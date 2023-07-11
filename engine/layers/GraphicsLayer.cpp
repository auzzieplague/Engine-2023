#include "GraphicsLayer.h"
#include "graphics/api/GraphicsAPI.h"

void GraphicsLayer::setApi(GraphicsAPI *api) {
    this->api = api;
    // let any graphics objects that contain their own setup methods know which API to call.
    Mesh::setApi(api);
    Terrain::setApi(api);
}

void GraphicsLayer::onAttach(Scene *scene) {
    Debug::show("[>] Graphics Attached");
    initialRenderingSetup(scene);
    Material::initialise();
}

void GraphicsLayer::initialRenderingSetup(Scene *scene) {
    meshConfig.shaderID = api->loadShader("general.vert", "general.frag");
    meshConfig.enable(flag(CULL_FACE));
//    meshConfig.enable(flag(ALPHA_BLENDING));
    meshConfig.enable(flag(DEPTH_TEST));
    meshConfig.setClearFlag(flag(CLEAR_COLOUR_BUFFER));
    meshConfig.setClearFlag(flag(CLEAR_DEPTH_BUFFER));

//    meshConfig.debugMode=true;
    api->updateRendererConfig(meshConfig);
    api->shaderSetProjection(scene->currentCamera->getProjectionMatrix());
    api->shaderSetView(scene->currentCamera->getViewMatrix());
}

void GraphicsLayer::render(Scene *scene) {
    // updatePosition shaders and set m_api properties
    api->updateRendererConfig(meshConfig);
    // camera might be mDirty
    checkDirtyCamera(scene);

    // collect meshes - todo: sort by shader
    std::vector<Mesh *> meshes;
    for (auto model: scene->modelsInScene) {
        meshes.insert(meshes.end(), model->mRootMesh->meshTree.begin(), model->mRootMesh->meshTree.end());
    }

    api->shaderSetCamera(scene->currentCamera);

    for (auto mesh: meshes) {
        api->shaderSetTransform(mesh->getWorldMatrix());
        api->shaderSetMaterial(mesh->getMaterial());
        api->renderMesh(mesh);
    }

    // todo - instance render the cubes using the same model
}

void GraphicsLayer::checkDirtyCamera(Scene *scene) const {
    if (scene->currentCamera->isDirty()) {
        api->shaderSetMat4("view", scene->currentCamera->getViewMatrix());
        scene->currentCamera->setDirty(false);
    }
}

unsigned int GraphicsLayer::flag(GraphicsFlag graphicsFlag) {
    // grab mapping from m_api for our enumerations
    return api->getFlag(graphicsFlag);
}

void GraphicsLayer::update(Scene *) {
    // pickup and exchange any modelsInSceneQueue that are ready

}
