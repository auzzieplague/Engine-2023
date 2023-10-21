#pragma once

enum TinkerDataType {
    TINKER_BYTE = 0x1400,
    TINKER_UNSIGNED_BYTE = 0x1401,
    TINKER_SHORT = 0x1402,
    TINKER_UNSIGNED_SHORT = 0x1403,
    TINKER_INT = 0x1404,
    TINKER_UNSIGNED_INT = 0x1405,
    TINKER_FLOAT = 0x1406,
};

enum TinkerDataSize {
    TINKER_1D = 1, //  for scalar data
    TINKER_2D = 2, //  for 2D data e.g. texture u,v
    TINKER_3D = 3, //  for 3D data e.g. vertex positions
    TINKER_4D = 4, //  for 4D data
};

class GPULayout {
public:
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


};
