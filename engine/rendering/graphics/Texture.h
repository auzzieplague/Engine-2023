#pragma once

#include <Tinker.h>

class GraphicsAPI; // forward declare

class Texture {
public:
    unsigned int textureId;
    int width, height;
    int format;
    unsigned int type;
    TextureWrap wrapMode;
    TextureFilter minFilter;
    TextureFilter magFilter;
    int mipMapLevels;
    bool isLoaded;
    const char* debugName;

    static GraphicsAPI *graphicsApi;

public:
    static void setGraphicsAPI(GraphicsAPI *api);

    Texture(int width, int height, int format) : textureId(0), width(width), height(height), format(0),
                wrapMode(TextureWrap::Clamp), minFilter(TextureFilter::Linear), magFilter(TextureFilter::Linear),
                mipMapLevels(1), isLoaded(false), debugName("Unnamed Texture") {
//        glGenTextures(1, &textureId);
    }

    ~Texture() {
//        if (textureId != 0) {
//            glDeleteTextures(1, &textureId);
//        }
    }

    Texture * generate();

    // ... Getter and Setter functions ...

    unsigned int getTextureId() const { return textureId; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    bool getIsLoaded() const { return isLoaded; }
    const char* getDebugName() const { return debugName; }

    void setWrapMode(TextureWrap wrapMode) {
        this->wrapMode = wrapMode;
//        glBindTexture(GL_TEXTURE_2D, textureId);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
//        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void setMinFilter(TextureFilter minFilter) {
        this->minFilter = minFilter;
//        glBindTexture(GL_TEXTURE_2D, textureId);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
//        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void setMagFilter(TextureFilter magFilter) {
        this->magFilter = magFilter;
//        glBindTexture(GL_TEXTURE_2D, textureId);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
//        glBindTexture(GL_TEXTURE_2D, 0);
    }

    // ... Other utility methods, like for loading from file, updating subregions, etc. ...

};
