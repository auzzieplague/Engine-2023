#pragma once
#include <GraphicsAPI.h>
#include "../../core/Window.h"
#include "Layer.h"
#include "graphics/GraphicsFlag.h"
#include "graphics/buffers/VertexBuffer.h"
#include "graphics/buffers/IndexBuffer.h"
#include "graphics/buffers/FrameBuffer.h"
#include "graphics/buffers/BufferContainer.h"
#include "graphics/VertexAttribute.h"
#include "graphics/RenderTarget.h"
class GraphicsLayer : public Layer {

public:
    std::string getName() override{
        return "Graphics Layer";
    };

    void setApi(GraphicsAPI *api) override {
        this->api = api;
    };

    void onAttach(Scene *) override ;

    void render(Scene *) override {

    };

    void update(Scene *) override {

    };

    void init(Scene *) override {
        api->queryCapabilities();
//        api->displayCapabilities();

        api->demoTriangle();
    };
};


