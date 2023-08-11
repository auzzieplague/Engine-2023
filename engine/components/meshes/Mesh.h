#pragma once
#include "../Component.h"
#include "MeshData.h"

class Mesh : public Component{
public:
    MeshData *mesh;
};
