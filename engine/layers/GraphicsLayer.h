#pragma once

#include "../../core/Window.h"
#include "Layer.h"
#include "../components/Geometry.h"
#include "graphics/api/RenderingConfig.h"
#include "graphics/GraphicsFlag.h"

/**
 * When instantiating this class we pass through a framework, which in turn sets m_up the function pointers
 * for OPENGL or other framework options
 */
class GraphicsLayer : public Layer {

public:
    /// testing
    unsigned int testMeshVAO{};
    Mesh *testMesh{};
    RenderingConfig singleRenderConfig;
    RenderingConfig instanceRenderConfig;
    RenderingConfig objectTrackerConfig;

    void setApi(GraphicsAPI *api) override;

    void onAttach(Scene *) override;

    void render(Scene *) override;

    void update(Scene *) override;

    void checkDirtyCamera(Scene *scene) const;

    void meshRenderConfig(Scene *scene);

    void objectTrackerRenderConfig(Scene *scene);

    void renderSingleMesh(Mesh *mesh) const;

    void renderInstancedMesh(Mesh *mesh, std::vector<glm::mat4> transforms);

    void updateMouseOverObject();

    bool checkDeferMesh(Mesh *mesh);
};
