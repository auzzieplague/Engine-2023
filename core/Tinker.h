#pragma once

#include <iostream>

// Determine the compiler and set the function signature macro accordingly
#if defined(__GNUC__) || defined(__clang__)
#define TINKER_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
#define TINKER_FUNC_SIG __FUNCSIG__
#else
#define TINKER_FUNC_SIG "Unknown Function"
#endif

// Define the TINKER_MISSING_OVERRIDE macro
#define TINKER_MISSING_OVERRIDE std::cout << TINKER_FUNC_SIG << " has no override function." << std::endl

#define TINKER_ARRAY_SIZE(myArray) (sizeof(myArray) / sizeof((myArray)[0]))


enum class TextureFilter {
    Nearest,  // Nearest-neighbor filtering
    Linear    // Linear interpolation filtering
};

enum class TextureWrap {
    Repeat,   // Repeat the texture
    Clamp     // Clamp texture coordinates to the edge
};