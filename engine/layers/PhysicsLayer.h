#pragma once

#include "Layer.h"
//#include <PxPhysicsAPI.h>
#include <PxPhysics.h>
#include <cooking/PxCooking.h>

class PhysicsLayer  : public Layer {

public:
    // declare variables
    physx::PxDefaultAllocator      mDefaultAllocatorCallback;
    physx::PxDefaultErrorCallback  mDefaultErrorCallback;
    physx::PxDefaultCpuDispatcher* mDispatcher = NULL;
    physx::PxTolerancesScale       mToleranceScale;

    physx::PxFoundation*           mFoundation = NULL;
    physx::PxPhysics*              mPhysics = NULL;

    physx::PxScene*                mScene = NULL;


    physx::PxPvd*                  mPvd = NULL;

//    void setApi(GraphicsAPI *api) override;

    void onAttach(Scene *) override;

//    void render(Scene *) override;
    void update(Scene *) override;

    void initPhysicsWorld();

    void processSpawnQueue(Scene *scene);

    physx::PxTriangleMesh* createTriangleMeshForModel(Model * model);

    void
    onCollision(const physx::PxContactPairHeader &pairHeader, const physx::PxContactPair *pairs, unsigned int nbPairs);
};