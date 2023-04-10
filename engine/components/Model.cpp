#pragma once

#include "Model.h"

Model *Model::createFromGeometry(Geometry::ShapeType shape, GeometryConfig config) {
    auto *model = new Model();
    model->mesh = new Geometry();
    switch(shape) {
        default:
            Debug::show("unsupported shape requested by model");
            break;
        case Geometry::ShapeType::Cube :
            dynamic_cast<Geometry *>(model->mesh)->buildCube(config);
            break;
        case Geometry::ShapeType::Sphere :
            dynamic_cast<Geometry *>(model->mesh)->buildSphere(config);
            break;
        case Geometry::ShapeType::Terrain :
            dynamic_cast<Geometry *>(model->mesh)->buildTerrain(config);
            break;
        case Geometry::ShapeType::Dome :
            dynamic_cast<Geometry *>(model->mesh)->buildDome(config);
            break;
        case Geometry::ShapeType::Torus :
            dynamic_cast<Geometry *>(model->mesh)->buildTorus(config);
            break;
        case Geometry::ShapeType::Capsule :
            dynamic_cast<Geometry *>(model->mesh)->buildCapsule(config);
            break;
        case Geometry::ShapeType::Cone :
            dynamic_cast<Geometry *>(model->mesh)->buildCone(config);
            break;
    }
    return model;
}