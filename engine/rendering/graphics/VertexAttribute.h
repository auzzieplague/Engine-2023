#pragma once

#include <GraphicsAPI.h>
#include <Tinker.h>

class BufferContainer;


class GraphicsAPI;

class VertexAttribute {
public:

    unsigned int index = 0;                 // Location of the vertex attribute
    int vertexType = TINKER_3D;
    int dataCount = 0;
    TinkerDataType dataType = TINKER_FLOAT;
    bool normalised{};                      // Whether data should be normalized
    const void *pointer = nullptr;          // Pointer to the first component of the vertex attribute
    unsigned int stride = 0;

    static GraphicsAPI *graphicsApi;
    static void setGraphicsAPI(GraphicsAPI *api) ;

    BufferContainer *applyToBuffer{};
    bool bufferCreated = false;

    explicit VertexAttribute(unsigned int index) : index(index) {
        this->vertexType = TINKER_3D;
        this->dataCount = 0;
        this->dataType = TINKER_FLOAT;
        this->normalised = false;
        this->pointer=(void *) nullptr;
        this->stride = 3*sizeof(float);
    }

    VertexAttribute * setAsTexture2D ( std::vector<glm::vec2> uvs) {
        this->vertexType = TINKER_2D;
        this->dataType = TINKER_FLOAT;
        this->normalised = false;
        this->dataCount = uvs.size();
        this->pointer= uvs.data();
        this->stride = sizeof(glm::vec2);
        return this;
    }

    VertexAttribute * setAsPositions3D (std::vector<glm::vec3> positions) {
        this->vertexType = TINKER_3D;
        this->dataType = TINKER_FLOAT;
        this->normalised = false;
        // this pointer is not being retained
        this->pointer= positions.data();
        this->dataCount = positions.size();
        this->stride = sizeof(glm::vec3);
        return this;
    }


    VertexAttribute * setVertexType(int type) { this->vertexType = type; return this;};
    VertexAttribute * setIndex(int _index) { this->index = _index; return this;};
    VertexAttribute * setSize(unsigned int _size) { this->dataCount = _size; return this;};
    VertexAttribute * setNormalised(int _normalised) { this->normalised = _normalised; return this;};
    VertexAttribute * setPointer(const void *_pointer) { VertexAttribute::pointer = _pointer; return this;};
    VertexAttribute * applyTo(BufferContainer * buffer);

};
