#pragma once

#include "../../core/Window.h"
#include "Layer.h"
//#include "graphics/api/GraphicsAPI.h"
#include "../components/Components.h"
#include "../components/Geometry.h"
#include "graphics/api/RenderingConfig.h"
#include "graphics/GraphicsFlag.h"

/**
 * When instantiating this class we pass through a framework, which in turn sets up the function pointers
 * for OPENGL or other framework options
 */
class GraphicsLayer : public Layer {

public:
    /// testing
    unsigned int testMeshVAO{};
    Mesh *testMesh{};
    RenderingConfig meshConfig;

    void setApi(GraphicsAPI *api) override;
    unsigned int flag(GraphicsFlag graphicsFlag);

    void onAttach(Scene *) override;

    void render(Scene *) override;

    void checkDirtyCamera(Scene *scene) const;

    void initialRenderingSetup(Scene *scene);
};
