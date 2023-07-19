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


void GraphicsLayer::objectTrackerRenderConfig(Scene *scene) {

    objectTrackerConfig.shaderID = api->loadShader("general.vert", "object_lookup.frag");
//    objectTrackerConfig.enable(api->getFlag((CULL_FACE)));
//    meshConfig.enable(api->getFlag((ALPHA_BLENDING)));
//    objectTrackerConfig.enable(api->getFlag((DEPTH_TEST)));
    objectTrackerConfig.setClearFlag(api->getFlag((CLEAR_COLOUR_BUFFER)));
    objectTrackerConfig.setClearFlag(api->getFlag((CLEAR_DEPTH_BUFFER)));
    objectTrackerConfig.clearColour = {0,0,0,1};
    api->beginRender(objectTrackerConfig);
    api->shaderSetProjection(scene->currentCamera->getProjectionMatrix());
    api->shaderSetView(scene->currentCamera->getViewMatrix());
}
void GraphicsLayer::render(Scene *scene) {
    /// merged both renders into this one function to better troubleshoot the issue
    /// next step is to manually add the clears and

    api->beginRender(objectTrackerConfig);
    api->shaderSetView(scene->currentCamera->getViewMatrix());

    std::vector<Mesh *> meshes;
    for (auto model: scene->modelsInScene) {
        meshes.insert(meshes.end(), model->mRootMesh->meshTree.begin(), model->mRootMesh->meshTree.end());
    }

    for (auto mesh: meshes) {
        api->shaderSetTransform(mesh->getWorldMatrix());
        api->shaderSetVec3("entityID", mesh->colourID);

//        api->shaderSetMaterial(mesh->getMaterial());
        api->renderMesh(mesh);
    }

    glFlush();
    glFinish();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    unsigned char data[4];
    glReadPixels(Input::m_mousePos.x,
                 this->currentScene->currentWindow->height - Input::m_mousePos.y,
                 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
    scene->mouseOverObjectID = data[0] + data[1] * 256 + data[2] * 256 * 256;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    api->beginRender(renderConfig);
    api->shaderSetView(scene->currentCamera->getViewMatrix());
//    api->shaderSetCamera(scene->currentCamera);
//    // camera might be mDirty
//    checkDirtyCamera(scene);
//
//    // collect meshes - todo: sort by shader
    for (auto model: scene->modelsInScene) {
        meshes.insert(meshes.end(), model->mRootMesh->meshTree.begin(), model->mRootMesh->meshTree.end());
    }
//
//    api->shaderSetCamera(scene->currentCamera);
//
glm::vec3 highlight;
    for (auto mesh: meshes) {
        if (scene->selectHoveredComponent && mesh->objectID == scene->mouseOverObjectID) {
            scene->selectComponent(mesh);
        }
        api->shaderSetTransform(mesh->getWorldMatrix());
        highlight = mesh->highlighted ? glm::vec3{2,2,2} : glm::vec3{1.0,1.0,1.0};

        api->shaderSetVec3("highlight", highlight);
        api->shaderSetMaterial(mesh->getMaterial());
        //todo update entityID only when clicking or maybe mouse move, not every frame
//        api->shaderSetVec3("entityID", mesh->colourID);
        api->renderMesh(mesh);
    }
////
//    api->endRender(renderConfig);
    // todo - instance render the cubes using the same model
    glFlush();
    glFinish();
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
