#pragma once

// base c++ includes
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <deque>
#include <map>
#include <cassert>
#include <random>
#include <cstdlib>
#include <ctime>

/// lib includes
#include <glm/glm.hpp>

/// our own includes
#include "Debug.h"

// type definitions
typedef unsigned int uint;
typedef unsigned char uchar;

struct HeightMap {
    int width;
    int height;
    float scale;
    float minHeight;
    float maxHeight;
    std::vector<unsigned int> indices;

    [[nodiscard]] const std::vector<unsigned int> &getIndices() const {
        return indices;
    }

    std::vector<float> vertexHeights;
    std::vector<float> vertices;
    std::vector<float> uvCoordinates;
    std::vector<float> normalVectors;
    std::vector<glm::vec4> colorData;

};