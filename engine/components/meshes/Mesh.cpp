
#include "../../layers/graphics/api/GraphicsAPI.h"
#include "Mesh.h"

GraphicsAPI *Mesh::api;

void Mesh::setApi(GraphicsAPI *api) {
    Mesh::api = api;
}
bool Mesh::readyCheck(){
    if (isReady) return true;

    // not all meshes will need to be rendered, but at the moment only rendering is using readyCheckk
    // we will need to subclass mesh into render and non render types
    if (this->gID == 0){
        isReady = true;
    }
    return isReady;
};
unsigned int Mesh::generateMeshID() {
    this->gID = api->setupMesh(this);
    if (this->gID == 0){
        Debug::show("Failed to generate meshID for " + getName());
    }
    return this->gID;
}
