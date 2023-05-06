
#include "Terrain.h"

const HeightMap &Terrain::getHeightMap() const {
    return mHeightMap;
}

HeightMap Terrain::loadHeightMap(const std::string &name) {
   return AssetManager::getHeightMap(name,1,-1,20);
    // todo populate Terrain using correct shape type in processModelSpawnQueue method
}


void Terrain::setCollider(ColliderConfig config)  {
    mCollider = new Collider(config);
    //terrains don't use mesh, rebuild using height map
//    mCollider->rebuild(mMesh);
//    this->mCollider->update(-m_transform.getPosition());

}
