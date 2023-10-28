#pragma once

#include <Tinker.h>



class Texture {
private:
    unsigned int textureId;
    int width, height;
    unsigned int format;
    unsigned int type;
    TextureWrap wrapMode;
    TextureFilter minFilter;
    TextureFilter magFilter;
    int mipMapLevels;
    bool isLoaded;
    const char* debugName;

public:
    Texture() : textureId(0), width(0), height(0), format(0), type(TINKER_2D),
                wrapMode(TextureWrap::Clamp), minFilter(TextureFilter::Linear), magFilter(TextureFilter::Linear),
                mipMapLevels(1), isLoaded(false), debugName("Unnamed Texture") {
//        glGenTextures(1, &textureId);
    }

    ~Texture() {
//        if (textureId != 0) {
//            glDeleteTextures(1, &textureId);
//        }
    }

    void initialise(int width, int height, unsigned int format, unsigned int type) {
        this->width = width;
        this->height = height;
//        this->format = format;
//        this->type = type;
//
//        glBindTexture(GL_TEXTURE_2D, textureId);
//        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, type, nullptr);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
//        glBindTexture(GL_TEXTURE_2D, 0);

        isLoaded = true;
    }

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
