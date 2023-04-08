#include "GraphicsLayer.h"
#include "graphics/api/GraphicsAPI.h"



void GraphicsLayer::setApi(GraphicsAPI *api) {
    this->api = api;
    Mesh::setApi(api);
}

void GraphicsLayer::onAttach(Scene *scene) {
    // setup mesh rendering config
    meshConfig.shaderID = api->loadShader("general.vert", "general.frag");
    meshConfig.disable(flag(CULL_FACE));
    api->updateRendererConfig(meshConfig);
    api->shaderSetMat4("projection",scene->currentCamera->getProjectionMatrix());
    api->shaderSetMat4("view",scene->currentCamera->getViewMatrix());

    // set projection matrix uniform



    auto *geometry = new Geometry();
//    geometry->buildQuad();
//        geometry->buildCube();
//        geometry->buildDome(0.5f,12);
        geometry->buildSphere(0.5f,20,20);
//        geometry->buildCapsule(0.5f,1.0f,16);
//        geometry->buildTorus(0.5f,0.1f,24,24); // slightly busted
//        geometry->buildCone(0.5f, 1.0f, 24); // busted

    geometry->transform.setPosition({0,0,-5});
    this->testMeshVAO = geometry->generateMeshID();

    testMesh = geometry;
}

void GraphicsLayer::render(Scene *scene) {
    // update shaders and set api properties
    api->updateRendererConfig(meshConfig);


    // send transform
    api->shaderSetMat4("transform",testMesh->transform.getModelMatrix());

    // render meshes
    api->renderMesh(testMesh);
}

unsigned int GraphicsLayer::flag(GraphicsFlag graphicsFlag) {
   // grab mapping from api for our enumerations
    return api->getFlag(graphicsFlag);
}
