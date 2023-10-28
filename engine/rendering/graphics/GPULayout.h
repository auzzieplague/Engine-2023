#pragma once

#include <GraphicsAPI.h>
#include <Tinker.h>

class BufferObject;


class GraphicsAPI;

class GPULayout {
public:
    static GraphicsAPI *graphicsApi;
    static void setGraphicsAPI(GraphicsAPI *api) ;

    BufferObject *applyToBuffer{};
    explicit GPULayout(unsigned int index) : index(index) {
        this->size = TINKER_3D;
        this->type = TINKER_FLOAT;
        this->normalised = false;
        this->stride = 3*sizeof (float);
        this->pointer=(void *) nullptr;
    }

    unsigned int index = 0;    // Location of the vertex attribute
    int size = TINKER_3D;              // Number of components per vertex attribute (1 to 4)
    TinkerDataType type = TINKER_FLOAT;   // Data type of each component
    bool normalised{};       // Whether data should be normalized
    int stride =  3 * sizeof(float);            // Byte offset between consecutive vertex attributes
    const void *pointer = nullptr;   // Pointer to the first component of the vertex attribute

    GPULayout * setSize(int _size) {this->size = _size; return this;};
    GPULayout * setIndex(int _index) {this->index = _index; return this;};
    GPULayout * setType(TinkerDataType _type) {this->type = _type; return this;};
    GPULayout * setNormalised(int _normalised) {this->normalised = _normalised; return this;};
    GPULayout * setStride(int _stride) {this->stride = _stride; return this;};

    GPULayout *applyTo(BufferObject * buffer);



};
