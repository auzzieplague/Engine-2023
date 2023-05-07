
#include "Terrain.h"
#include "../layers/graphics/api/GraphicsAPI.h"
GraphicsAPI *Terrain::m_api;

const HeightMap &Terrain::getHeightMap() const {
    return mHeightMap;
}

HeightMap Terrain::loadHeightMap(const std::string &name) {
   return AssetManager::getHeightMap(
           name,this->mHeightMap.scale,
           this->mHeightMap.minHeight,
           this->mHeightMap.maxHeight);
}


void Terrain::setCollider(ColliderConfig config)  {
    mCollider = new Collider(config);
    // terrain physics object gets built on spawn and is always static
    this->mCollider->update(-m_transform.getPosition());

}

unsigned int Terrain::generateMeshID() {
    this->m_gID = m_api->setupTerrain(&this->mHeightMap);
    if (this->m_gID == 0) {
        Debug::show("Failed to generate meshID for " + getName());
    }
    return this->m_gID;
}

void Terrain::setApi(GraphicsAPI *api) {
    Terrain::m_api = api;
}

