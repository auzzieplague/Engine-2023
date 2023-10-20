#pragma once
#include <GraphicsAPI.h>
#include "../../core/Window.h"
#include "Layer.h"
#include "graphics/GraphicsFlag.h"
#include "graphics/VertexBuffer.h"
#include "graphics/IndexBuffer.h"

class GraphicsLayer : public Layer {

public:
    std::string getName() override{
        return "Graphics Layer";
    };

    void setApi(GraphicsAPI *api) override {
        this->api = api;
        // let any graphics objects that contain their own setup methods know which API to call.
        Material::setGraphicsAPI(api);
        VertexBuffer::setGraphicsAPI(api);
        IndexBuffer::setGraphicsAPI(api);
        ShaderProgram::setGraphicsAPI(api);
        Shader::setGraphicsAPI(api);
        Mesh::setApi(api);
    };

    void onAttach(Scene *) override ;

    void render(Scene *) override {

    };

    void update(Scene *) override {

    };
};


