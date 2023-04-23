#pragma once

#include "Layer.h"
#include <PxPhysicsAPI.h>

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
    physx::PxMaterial*             mMaterial = NULL;

    physx::PxPvd*                  mPvd = NULL;

//    void setApi(GraphicsAPI *api) override;

    void onAttach(Scene *) override;

//    void render(Scene *) override;
    void update(Scene *) override;

};