#pragma once

#include "../Component.h"
#include "../Material.h"

class GraphicsAPI;

class Mesh : public Component {
    friend class Collider;

protected:
    Material m_material;
    Material m_material_original;
    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec2> m_UVs;
    std::vector<glm::vec3> m_normals;
    std::vector<unsigned int> m_indices;

    std::vector<glm::vec3> m_tangents;
    std::vector<glm::vec3> m_biTangents;

public:
    enum TOPOLOGY {
        POINTS,
        LINES,
        LINE_STRIP,
        TRIANGLES,
        TRIANGLE_STRIP,
        TRIANGLE_FAN,
    };

    Mesh *parentMesh = nullptr;
    Mesh *rootMesh = nullptr;
//    std::vector<Mesh *> subMeshes;
    std::vector<Mesh *> meshTree;

    void addMesh(Mesh *subMesh) {

        // todo : on component addChild - if mesh, call this rather than forcing developer to addMesh explicitly
        /*
         * Note: on construction this mesh is added to mesh tree, so mesh tree always contains self
         *
         */
        subMesh->parentMesh = this;
        childComponents.push_back(subMesh);
        // each mesh should know its parent and root, and be added to the root mesh tree

        // if this mesh has a parent mesh (is a child), update the rootMesh tree
        if (this->parentMesh) {
            // update existing submesh meshtree parent, root values accordingly
            for (auto nestedMesh: subMesh->meshTree) {
                nestedMesh->parentMesh = this;
                nestedMesh->rootMesh = this->rootMesh;
//                updateComponentWorldTransform(nestedMesh, this->getWorldTransform());
                nestedMesh->worldTransform.setPosition(this->worldTransform.getPosition()+nestedMesh->getLocalPosition());
                nestedMesh->updateCombinedTransform();
            }
            rootMesh->meshTree.insert(rootMesh->meshTree.end(), subMesh->meshTree.begin(), subMesh->meshTree.end());

            //todo update all submeshtree items world transform

        } else {
            // if this is the first child being added, make this the rootMesh
            subMesh->rootMesh = this;
            meshTree.push_back(subMesh);
            // apply this world transform to child
//            updateComponentWorldTransform(subMesh, this->getWorldTransform());

            subMesh->worldTransform.setPosition(this->worldTransform.getPosition()+subMesh->getLocalPosition());
            subMesh->updateCombinedTransform();
        }

    };




    void setVertices(const std::vector<glm::vec3> &mVertices);

    void setIndices(const std::vector<unsigned int> &mIndices);

    void setUVs(std::vector<glm::vec2> &UVs);

    void setNormals(const std::vector<glm::vec3> &mNormals);

    TOPOLOGY m_topology = TRIANGLES;
    unsigned int m_topologyID = 0; // updated in initMesh()
    unsigned int m_gID = 0;
    static GraphicsAPI *m_api;

    ObjectType getType() override {
        return ObjectType::OT_Mesh;
    };

    std::string getName() override {
        return "Mesh - name tbc";
    };

    bool isReady() override;

    Mesh() {
        meshTree.push_back(this);
    };

    static void setApi(GraphicsAPI *api);

    void setMaterial(const Material &material);

    void restoreMaterial();

    Material &getMaterial();

    [[nodiscard]] const std::vector<glm::vec3> &getVertices() const;

    [[nodiscard]] const std::vector<glm::vec2> &getUVs() const;

    [[nodiscard]] const std::vector<glm::vec3> &getNormals() const;

    [[nodiscard]] const std::vector<glm::vec3> &getTangents() const;

    [[nodiscard]] const std::vector<glm::vec3> &getBiTangents() const;

    [[nodiscard]] const std::vector<unsigned int> &getIndices() const;

    [[nodiscard]] unsigned int getID() const;

    /**
     * Note: not all meshes will require loading into video ram,
     * some meshes are only for collision. Some meshes, although in proximity to the view may never be seen,
     * so we will only generateMeshID when attempting to render an object that doesnt already have one.
     * @return
     */
    unsigned int generateMeshID();

    void calculateNormals();

    void calculateTangents();

    void applyPxTransform(const physx::PxTransform &pxTransform);

    void switchIndexOrder(bool clockwise = true);
};

