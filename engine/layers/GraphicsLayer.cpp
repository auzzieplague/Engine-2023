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
    renderConfig.shaderID = api->loadShader("general.vert", "general.frag");
//    renderConfig.shaderID = api->loadShader("general.vert", "object_lookup.frag");
    renderConfig.enable(api->getFlag((CULL_FACE)));
//    meshConfig.enable(api->getFlag((ALPHA_BLENDING)));
    renderConfig.enable(api->getFlag((DEPTH_TEST)));
    renderConfig.setClearFlag(api->getFlag((CLEAR_COLOUR_BUFFER)));
    renderConfig.setClearFlag(api->getFlag((CLEAR_DEPTH_BUFFER)));

//    meshConfig.debugMode=true;
    api->beginRender(renderConfig);
    api->shaderSetProjection(scene->currentCamera->getProjectionMatrix());
    api->shaderSetView(scene->currentCamera->getViewMatrix());
}

void GraphicsLayer::render(Scene *scene) {
//     updatePosition shaders and set m_api properties
//    api->beginRender(renderConfig);
//    // camera might be mDirty
//    checkDirtyCamera(scene);
//
//    // collect meshes - todo: sort by shader
//    std::vector<Mesh *> meshes;
//    for (auto model: scene->modelsInScene) {
//        meshes.insert(meshes.end(), model->mRootMesh->meshTree.begin(), model->mRootMesh->meshTree.end());
//    }
//
//    api->shaderSetCamera(scene->currentCamera);
//
//    for (auto mesh: meshes) {
//        api->shaderSetTransform(mesh->getWorldMatrix());
//        api->shaderSetMaterial(mesh->getMaterial());
//        //todo update entityID only when clicking or maybe mouse move, not every frame
////        api->shaderSetVec3("entityID", mesh->colourID);
//        api->renderMesh(mesh);
//    }
//
//    api->endRender(renderConfig);
    // todo - instance render the cubes using the same model
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
