#pragma once

#include <GraphicsBehaviour.h>
#include <Tinker.h>

class GraphicsAPI; // forward declare

class BaseBuffer {
public:

    static GraphicsAPI *graphicsApi;
    mutable unsigned int bufferID = 0;

    const void *data;
    size_t dataSize;
    unsigned int usage;

    BaseBuffer(const void *data, size_t dataSize, const char *usage);

    static void setGraphicsAPI(GraphicsAPI *api);

    [[nodiscard]] const void *getData() const { return data; }

    [[nodiscard]] size_t getDataSize() const { return dataSize; }

    [[nodiscard]] unsigned int getUsage() const { return usage; }

    virtual BaseBuffer *generate() {
        TINKER_MISSING_OVERRIDE;
        return this;
    };

    virtual BaseBuffer *bind() {
        TINKER_MISSING_OVERRIDE;
        return this;
    };
};
