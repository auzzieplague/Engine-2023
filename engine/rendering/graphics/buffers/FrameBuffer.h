#pragma once

class Texture;
class GraphicsAPI;

class FrameBuffer {

public:
    int height;
    int width;

    static GraphicsAPI *graphicsApi;
    mutable unsigned int bufferID = 0;


    static void setGraphicsAPI(GraphicsAPI *api);

    FrameBuffer (int width, int height){
        this->width = width;
        this->height = height;
    };

    FrameBuffer* generate();

    Texture * texture{};
};
