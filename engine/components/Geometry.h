#pragma once

#include "meshes/Mesh.h"

struct GeometryConfig {

    struct BoxConfig {
        float sizeX = 0.5f;
        float sizeY = 0.5f;
        float sizeZ = 0.5f;
    };

    struct CubeConfig {
      float size = 0.5f;
    };

    struct DomeConfig {
        float radius = 0.5f;
        unsigned int segments = 12;
    };

    struct SphereConfig {
        float radius =0.5f;
        unsigned int rings = 5;
        unsigned int sectors = 5;
    };

    struct CapsuleConfig {
        float radius = 0.5f;
        float halfLength = 1.0f;
        unsigned int segments = 16;
    };

    struct TorusConfig {
        float radius = 0.5f;
        float tubeRadius = 0.1f;
        int segments = 12;
        int sides = 12;
    };

    struct ConeConfig {
        float radius = 0.5f;
        float height = 1.0f;
        int segments = 24;
    };

    struct TerrainConfig {
        int width = 10;
        int height = 10;
        float minHeight = 0;
        float maxHeight = 0;
        float cellSize = 1;
        unsigned int seed = 456;
    };

     BoxConfig box;
     CubeConfig cube;
     DomeConfig dome;
     SphereConfig sphere;
     CapsuleConfig capsule;
     TorusConfig torus;
     ConeConfig cone;
     TerrainConfig terrain;
};

class Geometry : public Mesh {
    //inherits meshData
public:
    float pi = 3.1415926;
    float pi2 = 3.1415926 * 2;

    // todo add factory - usually at component level.
    // maintain a type in order to provide interface options for sectors, segments etc to rebuild shape
    enum class ShapeType {
        Quad,
        Cube,
        Dome,
        Sphere,
        Capsule,
        Torus,
        Cone,
        Terrain
    };

    Geometry() = default;;

    void buildQuad();
    void buildBox (GeometryConfig config ={});
    void buildCube(GeometryConfig config ={});

    void buildDome(GeometryConfig config ={});

    void buildSphere(GeometryConfig config ={});

    void buildCapsule(GeometryConfig config ={});

    void buildTorus(GeometryConfig config ={});

    void buildCone(GeometryConfig config ={});

    void buildTerrain(GeometryConfig config ={});
};


