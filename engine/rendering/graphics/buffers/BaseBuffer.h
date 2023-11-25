#pragma once

#include <GraphicsBehaviour.h>
#include <Tinker.h>

class GraphicsAPI; // forward declare

class BaseBuffer {
public:

    BufferContainer * containerObject{}; //associated container buffer object (VAO)
    static GraphicsAPI *graphicsApi;
    mutable unsigned int bufferID = 0;

    const void *data{};
    size_t byteCount{};
    unsigned int usage{};

    BaseBuffer()= default;;
    BaseBuffer(const void *data, size_t dataSize, const char *usage);

    static void setGraphicsAPI(GraphicsAPI *api);

    [[maybe_unused]] [[nodiscard]] const void *getData() const { return data; }

    [[nodiscard]] size_t getDataSize() const { return byteCount; }

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
