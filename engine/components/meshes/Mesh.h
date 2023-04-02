#pragma once

#include "../Component.h"

class Mesh : public Component {
public:
    Mesh() {}

    /**
     * load the 3D model data from a file, such as a .obj or .fbx file, into memory.
     * It may also perform any necessary preprocessing, such as calculating normals or tangents.
     */
    void loadModel();

    /**
     * take the model data and create a mesh object that can be rendered by the engine.
     * The mesh object should contain information such as vertex positions, texture coordinates, and indices.
     */
    void createMesh();

    /**
     * create a material object that defines how the mesh should be shaded.
     * involve loading textures, setting shader parameters, or defining lighting parameters.
     */
    void createMaterial();

};

