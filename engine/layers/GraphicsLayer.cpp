#include "GraphicsLayer.h"
#include "graphics/api/GraphicsAPI.h"


GraphicsLayer::GraphicsLayer(GraphicsAPI *api) {
    this->api = api;
    Mesh::setApi(api);
}

void GraphicsLayer::onAttach(Scene *) {
    // setup mesh rendering config
    meshConfig.shaderID = api->loadShader("general.vert", "general.frag");
    meshConfig.enable(flag(CULL_FACE));
    api->updateRendererConfig(meshConfig);


    auto *geometry = new Geometry();
//    geometry->buildQuad();
//        geometry->buildCube();
//        geometry->buildDome(0.5f,12);
        geometry->buildSphere(0.5f,20,20);
//        geometry->buildCapsule(0.5f,1.0f,16);
//        geometry->buildTorus(0.5f,0.1f,24,24); // slightly busted
//        geometry->buildCone(0.5f, 1.0f, 24); // busted

    this->testMeshVAO = geometry->generateMeshID();

    testMesh = geometry;
}

void GraphicsLayer::render(Scene *) {

    // update shaders and set api properties
    api->updateRendererConfig(meshConfig);

    // render meshes
    api->renderMesh(testMesh);
}

unsigned int GraphicsLayer::flag(GraphicsFlag graphicsFlag) {
   // grab mapping from api for our enumerations
    return api->getFlag(graphicsFlag);
}
