#pragma once

#include "Model.h"
#include "../AssetManager.h"

// todo load terrain using test_map in
class Terrain: public Model {
protected:
    HeightMap mHeightMap;
public:

    ObjectType getType() override {
        return ObjectType::OT_Terrain;
    };
    [[nodiscard]] const HeightMap &getHeightMap() const;

    explicit Terrain(const std::string& assetName):  Model (){
        // initially just load heightmap portion as the terrain but will need blend map and other terrain
        // details which will be nested under terrain, hieghtmap is just 1 of the components
        this->mHeightMap = loadHeightMap(assetName);
    }

    static HeightMap loadHeightMap(const std::string& name);

    void setCollider(ColliderConfig config);
};

