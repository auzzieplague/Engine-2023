#pragma once

#include "meshes/Mesh.h"


class Geometry : public Mesh {
    //inherits meshData
public:
    float pi = 3.1415926;
    float pi2 = 3.1415926 * 2;

    // todo add factory - usually at component level.
    // maintain a type in order to provide interface options for sectors, segments etc to rebuild shape
    enum geometryType {
        CUBE, PLANE
    };

    Geometry() = default;;

    void buildQuad();

    void buildCube();

    void buildDome(float radius, unsigned int segments);

    void buildSphere(float radius, unsigned int rings, unsigned int sectors);

    void buildCapsule(float radius, float halfLength, unsigned int segments);

    void buildTorus(float radius, float tubeRadius, int segments, int sides);

    void buildCone(float radius, float height, int segments);

    void buildTerrain(int width, int height, float minHeight, float maxHeight, float cellSize);
};


