#pragma once

#include <GraphicsAPI.h>
#include <Tinker.h>

class BufferContainer;


class GraphicsAPI;

class VertexAttribute {
public:

    unsigned int index = 0;                 // Location of the vertex attribute
    int vertexType = TINKER_3D;
    unsigned int byteSize = sizeof(float);
    TinkerDataType dataType = TINKER_FLOAT;
    bool normalised{};                      // Whether data should be normalized
    const void *pointer = nullptr;          // Pointer to the first component of the vertex attribute

    static GraphicsAPI *graphicsApi;
    static void setGraphicsAPI(GraphicsAPI *api) ;

    BufferContainer *applyToBuffer{};
    bool bufferCreated = false;

    explicit VertexAttribute(unsigned int index) : index(index) {
        this->vertexType = TINKER_3D;
        this->byteSize =  sizeof(float);
        this->dataType = TINKER_FLOAT;
        this->normalised = false;
        this->pointer=(void *) nullptr;
    }

    VertexAttribute * setAsTexture2D (const void *_pointer) {
        this->vertexType = TINKER_2D;
        this->byteSize =  sizeof(float);
        this->dataType = TINKER_FLOAT;
        this->normalised = false;
        this->pointer=_pointer;
        return this;
    }

    VertexAttribute * setAsPositions3D (const void *_pointer) {
        this->vertexType = TINKER_3D;
        this->byteSize =  sizeof(float);
        this->dataType = TINKER_FLOAT;
        this->normalised = false;
        this->pointer=_pointer;
        return this;
    }


    VertexAttribute * setVertexType(int type) { this->vertexType = type; return this;};
    VertexAttribute * setIndex(int _index) { this->index = _index; return this;};
    VertexAttribute * setSize(unsigned int _size) { this->byteSize = _size; return this;};
    VertexAttribute * setNormalised(int _normalised) { this->normalised = _normalised; return this;};
    VertexAttribute * setPointer(const void *_pointer) { VertexAttribute::pointer = _pointer; return this;};
    VertexAttribute * applyTo(BufferContainer * buffer);

};
