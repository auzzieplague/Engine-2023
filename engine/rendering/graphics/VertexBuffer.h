#pragma once

class GraphicsAPI; // forward declare

class VertexBuffer {
public:
    const void *data;
    size_t dataSize;
    unsigned int usage;
    static GraphicsAPI *graphicsApi;

public:
    static void setGraphicsAPI(GraphicsAPI *api);

    VertexBuffer(const void *data, size_t dataSize, const char* usage);

    mutable unsigned int bufferID = 0;

    [[nodiscard]] const void *getData() const { return data; }

    [[nodiscard]] size_t getDataSize() const { return dataSize; }

    [[nodiscard]] unsigned int getUsage() const { return usage; }

    VertexBuffer* generate();
    VertexBuffer* bind();
};
