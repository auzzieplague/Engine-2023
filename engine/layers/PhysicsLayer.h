#pragma once

#include "Layer.h"
#include "../components/Terrain.h"
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

    bool flush = false;

    void onAttach(Scene *) override;

    void update(Scene *) override;

    void appendToGui(Scene *scene) override;

    void initPhysicsWorld();

    void processModelSpawnQueue(Scene *scene);

#include <PxPhysicsAPI.h>


    physx::PxTriangleMesh* createTriangleMeshForModel(Model * model);

//    physx::PxHeightFieldGeometry createHeightGeometry(Terrain *model);
};