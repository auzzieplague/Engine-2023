#include <iostream>
#include "../engine/Engine.h"
#include "../engine/layers/CollisionLayer.h"

Model *testSphere;

void sphereCollisionTesting(Scene *scene) {

    auto object1 = Model::createFromGeometry(Geometry::ShapeType::Sphere);
    object1->setCollider();
    object1->setPosition({2, 0, -12});

    auto object2 = Model::createFromGeometry(Geometry::ShapeType::Cube);
    object2->setCollider();
    object2->setPosition({2, 2, -12});

    auto object3 = Model::createFromGeometry(Geometry::ShapeType::Dome);
    object3->setCollider();
    object3->setPosition({-2.5, 0, -12});


    auto object4 = Model::createFromGeometry(Geometry::ShapeType::Torus);
    object4->setCollider();
    object4->setPosition({0, 2, -12});

    scene->addComponent(object2);
    scene->addComponent(object3);
    scene->addComponent(object1);
    scene->addComponent(object4);

    int start = 10;
    int end = 20;
    int space = 1;

    auto test = Model::createFromGeometry(Geometry::ShapeType::Cube,
                                          GeometryConfig{.cube {.size=2}});
    test->setPosition({start+4.2, start+4.2, start+4.2});
    test->setCollider();
    scene->addComponent(test);

    for (int x = start; x < end; x+=space) {
        for (int z = start; z < end; z+=space) {
            for (int y = start; y < end; y+=space) {
                auto spot = Model::createFromGeometry(Geometry::ShapeType::Sphere,
                                                      GeometryConfig{.sphere {.radius =.1, .rings =3, .sectors =6}});
                spot->setPosition({x, y, z});
                spot->setCollider();
                scene->addComponent(spot);
            }
        }
    }
}

void setupScene(Scene *scene) {

//    sphereCollisionTesting(scene);

    auto *terrain1 = Model::createFromGeometry(Geometry::ShapeType::Terrain);
    terrain1->setPosition({-8, -2, -15});
    terrain1->setCollider();
    scene->addComponent(terrain1);


    testSphere = Model::createFromGeometry(Geometry::ShapeType::Sphere,
                                           GeometryConfig{.sphere {.radius =.5, .rings =6, .sectors =6}});
    testSphere->setPosition({0, 0, -12});
    testSphere->setCollider();
    scene->addComponent(testSphere);

    // then point / face collision

    // then octree to break down world and also meshes

}

void count_points(const Octree& octree, std::vector<int>& point_counts, int node_index=0) {
    // Base case: if the node is a leaf, increment the point count for its octant
    if (octree.is_leaf(node_index)) {
        int octant_index = octree.get_octant_index(node_index);
        point_counts[octant_index]++;
        return;
    }

    // Recursive case: traverse all child nodes and count the points in each of their octants
    for (int i = 0; i < 8; ++i) {
        int child_node_index = octree.get_child_node_index(node_index, i);
        if (!octree.is_leaf(child_node_index)) {
            count_points(octree, point_counts, child_node_index);
        }
    }
}

void testOctree (){
    // Create an Octree that spans from (-1, -1, -1) to (1, 1, 1) and has a depth of 2
    Octree octree(glm::vec3(-1.f), glm::vec3(1.f), 2);

    // Generate 1000 random points in the range (-1, -1, -1) to (1, 1, 1)
    std::vector<glm::vec3> points;
    for (int i = 0; i < 1000; ++i) {
        float x = static_cast<float>(rand()) / RAND_MAX * 2.f - 1.f;
        float y = static_cast<float>(rand()) / RAND_MAX * 2.f - 1.f;
        float z = static_cast<float>(rand()) / RAND_MAX * 2.f - 1.f;
        points.emplace_back(x, y, z);
    }

    // Insert the points into the Octree
    octree.insert(points);

    // Count the number of points in each octant
    std::vector<int> point_counts(8);
    count_points(octree, point_counts);

    // Print the point counts
    for (int i = 0; i < 8; ++i) {
        std::cout << "Octant " << i << ": " << point_counts[i] << " points\n";
    }

}

int main() {

    testOctree();
//
//    Engine *engine = Engine::getInstance();
//    engine->setGraphicsApi(new API_OpenGL());
//    engine->attachLayer(new WindowLayer());
//    engine->attachLayer(new GraphicsLayer());
//    engine->attachLayer(new CollisionLayer());
//
//    //setup interaction layer and scene together to inject a test model
//    auto *interactionLayer = new InteractionLayer();
//    engine->attachLayer(interactionLayer);
//    setupScene(engine->currentScene);
//    interactionLayer->selectedModel = testSphere;
//
//    Debug::show("[->] Use 'R' to generate collision report");
//    Debug::show("[->] Use NumPad 4862+- to navigate test");
//
//    engine->start();
//    Debug::show("done");
}
