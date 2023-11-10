
#include "Texture.h"
#include <GraphicsAPI.h> // override forward declaration of graphics api here

GraphicsAPI * Texture::graphicsApi;

void Texture::setGraphicsAPI(GraphicsAPI *api) {
    Texture::graphicsApi = api;
}

Texture * Texture::generate() {
    Texture::graphicsApi->createTexture(this);
    return this;
}
