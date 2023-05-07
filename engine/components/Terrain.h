#pragma once

#include "Model.h"
#include "../AssetManager.h"

// todo load terrain using test_map in
class Terrain : public Model {
private:
    static GraphicsAPI * m_api;
    unsigned int m_gID=0;

protected:
    HeightMap mHeightMap;
public:


    bool isReady() {
        if (m_ready) return true;

        if (this->m_gID != 0) {
            m_ready = true;
        }

        return m_ready;
    }

    ObjectType getType() override {
        return ObjectType::OT_Terrain;
    };

    [[nodiscard]] unsigned int getID() const {
        return this->m_gID;
    }

    [[nodiscard]] const std::vector<unsigned int> &getIndices() const {
        return this->mHeightMap.getIndices();
    }


    [[nodiscard]] const HeightMap &getHeightMap() const;

    explicit Terrain(const std::string &assetName, float scale = 1, float minHeight = 0, float maxHeight = 255)
            : Model() {
        // re-use the heightmap to store details before overriding them with the loaded heightmap data
        this->setScale(glm::vec3{scale,scale,scale});
        this->mHeightMap.minHeight = minHeight;
        this->mHeightMap.maxHeight = maxHeight;
        this->mHeightMap.scale = scale;
        // heightmap is used to generate the physics heightmap
        this->mHeightMap = loadHeightMap(assetName);

        // mesh used for rendering - can also be used for physics but not as performant
//        this->mMesh = loadTerrain(assetName);

    }

    HeightMap loadHeightMap(const std::string &name);

    void setCollider(ColliderConfig config);

    unsigned int generateMeshID();

    static void setApi(GraphicsAPI *api);

};

