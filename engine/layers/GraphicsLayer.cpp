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
    // camera might be m_dirty
    checkDirtyCamera(scene);

    // collect meshes - todo: sort by shader
    std::vector<Mesh *> meshes;
    for (auto model: scene->modelsInScene) {
        meshes.insert(meshes.end(), model->rootMesh->meshTree.begin(), model->rootMesh->meshTree.end());
    }

        api->shaderSetCamera(scene->currentCamera);

    for( auto mesh: meshes ) {

        //todo on setPosition etc, will need to build worldTransforms for children
        // getmatrix() will need to return worldMatrix - will use existing transform as local transforms.
        // were adding child  meshes to childComponents ... trying to keep this functionality general
        // other components might be added to a mesh, light, socket etc ... tbc
        api->shaderSetTransform(mesh->getMatrix());
        api->shaderSetMaterial(mesh->getMaterial());
        api->renderMesh(mesh);
    }
//
//    for (auto model: scene->modelsInScene) {
//
//        // need to updatePosition model matrix before each frame - if dirty
//        api->shaderSetTransform(model->getMatrix());
//        // todo model can have many meshes
//        api->shaderSetMaterial(model->rootMesh->getMaterial());
//        api->renderMesh(model->rootMesh);
//    }


    /// note currently rendering terrain as mesh for initial testing - fix scaling
    // render terrains and skybox first to cull overdraw
//    for (auto terrain: scene->terrainsToRender) {
//        api->shaderSetTransform(terrain->getMatrix());
//        // todo terrains have multiple materials
//        api->renderTerrain(terrain);
//    }

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
