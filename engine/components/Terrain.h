#pragma once

#include "Model.h"
#include "../AssetManager.h"

// todo load terrain using test_map in
class Terrain: public Model {
private:
    HeightMap mHeightMap;
public:
    [[nodiscard]] const HeightMap &getHeightMap() const;

    void loadHeightMap(const std::string& name) {
       this->mHeightMap = AssetManager::getHeightMap("test_map");
       // todo populate Terrain using correct shape type in processSpawnQueue method
    }
};

