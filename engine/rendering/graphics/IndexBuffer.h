#pragma once
class GraphicsAPI; // forward declare

class IndexBuffer {
public:
    const unsigned int *data;
    size_t dataSize;
    unsigned int usage;
    static GraphicsAPI *graphicsApi;

public:
    static void setGraphicsAPI(GraphicsAPI *api);

    IndexBuffer(const unsigned int *data, size_t dataSize, const char* usage);

    mutable unsigned int bufferID = 0;

    [[nodiscard]] const unsigned int *getData() const { return data; }

    [[nodiscard]] size_t getDataSize() const { return dataSize; }

    [[nodiscard]] unsigned int getUsage() const { return usage; }

    IndexBuffer* generate();
    IndexBuffer* bind();
};