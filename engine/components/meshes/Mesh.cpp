
#include "../../layers/graphics/api/GraphicsAPI.h"
#include "Mesh.h"

GraphicsAPI *Mesh::api;

void Mesh::setApi(GraphicsAPI *api) {
    Mesh::api = api;
}

unsigned int Mesh::generateMeshID() {
    this->gID = api->setupMesh(this);
    return this->gID;
}
