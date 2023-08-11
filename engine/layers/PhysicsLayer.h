#pragma once

#include "Layer.h"
#include "../components/Terrain.h"
#include "graphics/api/RenderingConfig.h"
#include <PxPhysicsAPI.h>

class PhysicsLayer  : public Layer {

public:
    physx::PxDefaultAllocator      mDefaultAllocatorCallback;
    physx::PxDefaultErrorCallback  mDefaultErrorCallback;
    physx::PxDefaultCpuDispatcher* mDispatcher = nullptr;
    physx::PxTolerancesScale       mToleranceScale;
    physx::PxFoundation*           mFoundation = nullptr;
    physx::PxPhysics*              mPhysics = nullptr;
    physx::PxScene*                mScene = nullptr;
    physx::PxPvd*                  mPvd = nullptr;

    static bool showCollisionMeshes;

    RenderingConfig renderConfig;
    void collisionRenderConfig(Scene *);
    bool flush = false;

    void onAttach(Scene *) override;

    void update(Scene *) override;

    void render(Scene *) override;

    void appendToGui(Scene *scene) override;

    void initPhysicsWorld();

    void processModelSpawnQueue(Scene *scene);

    physx::PxTriangleMesh* createTriangleMeshForModel(Model * model);

    void renderCollisionMesh(MeshData *mesh);
};