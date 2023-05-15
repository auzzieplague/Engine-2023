#include <PxSimulationEventCallback.h>
#include <PxPhysicsAPI.h>
#include <cooking/PxCooking.h>
#include "PhysicsLayer.h"
#include "../components/Terrain.h"

void PhysicsLayer::onAttach(Scene *) {
    Debug::show("[>] Physics Attached");
    initPhysicsWorld();
}

void PhysicsLayer::update(Scene *scene) {
    // process spawn queues
    this->processModelSpawnQueue(scene);
    this->processTerrainSpawnQueue(scene);

    physx::PxTransform transform;
    //updatePosition positions of models
    for (auto model: scene->modelsWithPhysics) {
        transform = model->mPhysicsBody->getGlobalPose();
         model->applyPxTransform(transform);
    }

    mScene->simulate(1.0f / 60.0f);
    mScene->fetchResults(true);
}

void PhysicsLayer::initPhysicsWorld() {
    // init physx
    mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, mDefaultAllocatorCallback, mDefaultErrorCallback);
    if (!mFoundation) throw ("PxCreateFoundation failed!");
    mPvd = PxCreatePvd(*mFoundation);
    physx::PxPvdTransport *transport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);

    mPvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);
    mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, physx::PxTolerancesScale(), true, mPvd);
    mToleranceScale.length = 100;        // typical length of an object
    mToleranceScale.speed = 981;         // typical speed of an object, gravity*1s is a reasonable choice

    physx::PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());
    sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
    mDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
    sceneDesc.cpuDispatcher = mDispatcher;
    sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
    mScene = mPhysics->createScene(sceneDesc);

    physx::PxPvdSceneClient *pvdClient = mScene->getScenePvdClient();
    if (pvdClient) {
        pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
        pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
        pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
    }
}

physx::PxTriangleMesh *PhysicsLayer::createTriangleMeshForModel(Model *model) {
// Create the triangle mMesh descriptor
    auto vertices = model->mMesh->getVertices();
    auto indices = model->mMesh->getIndices();

    // Get the scale matrix of the model
//    glm::vec3 scale = model->getScale();
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), model->getScale());

    // Scale the vertices of the mesh
    for (auto& vertex : vertices)
    {
        glm::vec4 scaledVertex = scaleMatrix * glm::vec4(vertex, 1.0f);
        vertex = glm::vec3(scaledVertex);
    }

    // Create the triangle mMesh descriptor
    physx::PxTriangleMeshDesc meshDesc;
    meshDesc.points.count = vertices.size();
    meshDesc.points.stride = sizeof(glm::vec3);
    meshDesc.points.data = vertices.data();
    meshDesc.triangles.count = indices.size() / 3;
    meshDesc.triangles.stride = 3 * sizeof(unsigned int);
    meshDesc.triangles.data = indices.data();

    // triangles appeared to be coming out backwards in PVD
    meshDesc.flags = physx::PxMeshFlags(physx::PxMeshFlag::eFLIPNORMALS); // <-- set the eFLIPNORMALS flag

    // Create the cooking object
    physx::PxTolerancesScale scale;
    physx::PxCookingParams params(scale);
    physx::PxCooking *cooking = PxCreateCooking(PX_PHYSICS_VERSION, mPhysics->getFoundation(), params);

    // Create the triangle mMesh in the PhysX SDK
    physx::PxTriangleMesh *triangleMesh = nullptr;
    physx::PxDefaultMemoryOutputStream writeBuffer;
    if (cooking->cookTriangleMesh(meshDesc, writeBuffer)) {
        physx::PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());
        triangleMesh = mPhysics->createTriangleMesh(readBuffer);
    }

    cooking->release();

    return triangleMesh;
}


physx::PxHeightFieldGeometry PhysicsLayer::createHeightGeometry(Terrain *model) {
    physx::PxHeightFieldGeometry hfGeom;
    physx::PxHeightFieldDesc hfDesc;
    hfDesc.format = physx::PxHeightFieldFormat::eS16_TM;
    HeightMap heightMap = model->getHeightMap();
    hfDesc.nbColumns = heightMap.width;
    hfDesc.nbRows = heightMap.height;

    // samples inst just vertex heights it's also material 1 and 2 for triangles
    std::vector<physx::PxHeightFieldSample> samples;
    samples.resize(hfDesc.nbRows * hfDesc.nbColumns);
    int i=0;
    for (int row =0; row < hfDesc.nbRows ; row++){
    for (int col =0; col < hfDesc.nbColumns ; col++){
        samples[i].height = heightMap.vertexHeights[i];
        samples[i].materialIndex0 = 2;
        samples[i].materialIndex1 = 3;
        i++;
    }}

    hfDesc.samples.data = samples.data();

    if (hfDesc.samples.data== nullptr){
        std::cout<<"busted";
    }

    hfDesc.samples.stride = sizeof(physx::PxHeightFieldSample);

    // Create the cooking object
    physx::PxTolerancesScale scale;
    physx::PxCookingParams params(scale);
    physx::PxCooking *cooking = PxCreateCooking(PX_PHYSICS_VERSION, mPhysics->getFoundation(), params);

    // Create height field geometry
    physx::PxHeightField *heightField = nullptr;
    physx::PxDefaultMemoryOutputStream writeBuffer;
    if (cooking->cookHeightField(hfDesc, writeBuffer)) {
        physx::PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());
        heightField = mPhysics->createHeightField(readBuffer);

        /// need to ensure widths, heights, scales are matching - here there is no width!!
        hfGeom = physx::PxHeightFieldGeometry(heightField, physx::PxMeshGeometryFlags(),
                                              heightMap.scale,
                                              heightMap.scale,
                                              heightMap.scale);
    }

    cooking->release();
    return hfGeom;
}

void PhysicsLayer::processModelSpawnQueue(Scene *scene) {

    if (scene->modelsWithPhysicsQueue.size() == 0) return;
    // pull off the next item this frame
    auto model = scene->modelsWithPhysicsQueue.front();
    scene->modelsWithPhysicsQueue.pop_front();

    // use the ColliderConfig for physics config
    ColliderConfig config = model->mCollider->getConfig();
    physx::PxMaterial *mMaterial = mPhysics->createMaterial(config.material.staticFriction,
                                                            config.material.dynamicFriction,
                                                            config.material.restitution);

    physx::PxShape *shape;
    physx::PxTriangleMesh *triangleMesh; // refactor and remove after testing
    physx::PxHeightFieldGeometry hfGeom; // refactor and remove

    /**
     * Regarding Transform of physx objects,
     * Our shapes being passed to Physx need scaling up to match the objects transform when rendering.
     * - we cannot pass scale as a transform variable, only position and rotation, scale must be handled when
     *   initialising shape / vertices.
     * - sphere geometry doesnt accept rotational values so we need to pass different transform params based on shape
     */
   glm::vec3 size = model->mCollider->getSize();
    switch (config.shape) {
        case config.Box:
            //size will be based on aabb
            shape = mPhysics->createShape(physx::PxBoxGeometry(
                    size.x ,
                    size.y ,
                    size.z ), *mMaterial);
            break;

        case config.Mesh:
            triangleMesh = createTriangleMeshForModel(model);
            if (triangleMesh) {
                shape = mPhysics->createShape(physx::PxTriangleMeshGeometry(triangleMesh), *mMaterial);
            }
            break;
        case config.Sphere:
        default:
            // m_size based on scale and radius of X, no support for ellipses
            shape = mPhysics->createShape(physx::PxSphereGeometry(size.x), *mMaterial);
            break;
    }


    /*
     * Build correct transform parameters - Different shapes have different transform params,
     * for example sphere geometry cannot have a rotational component.
     */
    physx::PxTransform buildTransform;  // different shapes have different transform properties
    auto position = model->getPosition();
    switch (config.shape) {
        case config.Box:
        case config.Mesh:
            buildTransform = model->getPxTransform();
            break;
        default:
            buildTransform = physx::PxTransform(physx::PxVec3(position.x,position.y,position.z));
            break;
    }

    // apply transform and instantiate correct physics body type
    switch (config.type) {
        case config.Dynamic:
            model->mPhysicsBody = mPhysics->createRigidDynamic(buildTransform);
            break;
        default:
            model->mPhysicsBody = mPhysics->createRigidStatic(buildTransform);
    }

    model->mPhysicsBody->attachShape(*shape);
    mScene->addActor(*model->mPhysicsBody);
    shape->release();

    // now everything is ready, push this model into the physics array
    scene->modelsWithPhysics.push_back(model);

}

void PhysicsLayer::processTerrainSpawnQueue(Scene *scene) {

    if (scene->terrainsWithPhysicsQueue.size() == 0) return;
    // pull off the next item this frame
    auto terrain = scene->terrainsWithPhysicsQueue.front();
    scene->terrainsWithPhysicsQueue.pop_front();

    ColliderConfig config = terrain->mCollider->getConfig();

    physx::PxMaterial *mMaterial = mPhysics->createMaterial(config.material.staticFriction,
                                                            config.material.dynamicFriction,
                                                            config.material.restitution);
    glm::vec3 p = terrain->getPosition();
    physx::PxTransform t(physx::PxVec3(p.x, p.y, p.z));

    physx::PxHeightFieldGeometry hfGeom=createHeightGeometry(terrain);

    physx::PxShape *shape = mPhysics->createShape(physx::PxHeightFieldGeometry(hfGeom), *mMaterial);
    switch (config.type) {
        case config.Dynamic:
            terrain->mPhysicsBody = mPhysics->createRigidDynamic(t);
            break;
        default:
            terrain->mPhysicsBody = mPhysics->createRigidStatic(t);
    }

    terrain->mPhysicsBody->attachShape(*shape);
    mScene->addActor(*terrain->mPhysicsBody);
    shape->release();

    // now everything is ready, push this terrain into the physics array
    scene->modelsWithPhysics.push_back(terrain);
}



