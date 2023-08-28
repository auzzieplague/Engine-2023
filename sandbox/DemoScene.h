
Model *playerObject;

Model *modelWithSubMeshes(bool physics = true) {
    ColliderConfig config{};
    Material material;

    material.loadFromAsset("mats_ground", "gray-bricks1");

    auto *model = Model::createWithGeometry(Geometry::ShapeType::Sphere);
    model->setName("model");
    model->setLocalRotation(glm::vec3(-30, 0, -25));
    model->setMaterial(material);
    model->setLocalScale(1);
    model->setPosition(glm::vec3(0, 0, -20));
    model->setSelectable();

    float offset = 1;
    glm::vec3 positions[] = {
            glm::vec3(-offset, -offset, -offset),
            glm::vec3(offset, -offset, -offset),
            glm::vec3(-offset, offset, -offset),
            glm::vec3(offset, offset, -offset),
            glm::vec3(-offset, -offset, offset),
            glm::vec3(offset, -offset, offset),
            glm::vec3(-offset, offset, offset),
            glm::vec3(offset, offset, offset),
    };

    int count = 7;
    for (int n = count; n >= 0; n--) {
        auto subMesh = AssetManager::loadMeshFromFile("geometry/box.fbx");
        subMesh->setName("sub mesh " + std::to_string(n));
        subMesh->setLocalScale(0.5f);
        subMesh->setPosition(positions[n]); // should be relative to parent mesh
        subMesh->setSelectable();
        material.setAmbientColor(glm::vec3(n * (1 / (count ? count : 1)), 0, 0));
        subMesh->setMaterial(material);
        subMesh->getMaterial().randomAmbientColor();
        model->mRootMesh->addChild(subMesh);
    }
    //todo make box same size as demo corners

    if (physics) {
//        model->autoPhysics();
        auto *collisionMesh = new Geometry();
        collisionMesh->buildCube(GeometryConfig{.cube{.size=1}, .sphere{.radius=2}});
        model->setCollisionMesh(collisionMesh);
        config.shape = config.Box;
        config.type = config.Dynamic;
        model->setCollider(config);
    }

    return model;
}

Model *terrainModel() {
    ColliderConfig config{};
    Material material;
    material.loadFromAsset("mats_ground", "grass1");

    auto *terrain1 = new Model();
    terrain1->getMeshFromHeightMap("test_map_64");
    Mesh *mesh = terrain1->getRootMesh();

//    Debug::show("Mesh Before and After");
//    Debug::show(mesh->getVertices().size());
//    terrain1->getRootMesh()->reduceMeshData(); // todo find new algorithm
//    Debug::show(mesh->getVertices().size());

    terrain1->setLocalScale({100, 10, 100});
    terrain1->setPosition({0, -20, -20});
    // todo 0 rotations cause build issues
    terrain1->setLocalRotation({1, 1, 1});
    terrain1->setMaterial(material);
    config = {.shape=config.Mesh, .type=config.Static};
    terrain1->setCollider(config);
    return terrain1;
}

void setupScene(Scene *scene) {

    playerObject = modelWithSubMeshes(true);
    scene->addComponent(playerObject);

    auto assimpModel = AssetManager::loadModelFromFile("../assets/models/testModel.obj");
    assimpModel->mRootMesh->setMaterial(*Material::defaultMaterial);
    assimpModel->setPosition({1, 1, -20});
    assimpModel->autoPhysics(); // todo - build automatic hull
    scene->addComponent(assimpModel);

    /// todos:
    //add physics to loaded models
    // fix autoscale() on import
    // save scene
    // load scene

    auto jsonModel = AssetManager::loadModel("testModel");
    jsonModel->mRootMesh->setMaterial(*Material::defaultMaterial);
    scene->addComponent(jsonModel);

    auto terrain = terrainModel();
    scene->addComponent(terrain);

    scene->currentCamera->setPosition({0, 0, 20});
}
