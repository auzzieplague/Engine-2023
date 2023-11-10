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
    TINKER_1D [[maybe_unused]] = 1, //  for scalar data
    TINKER_2D [[maybe_unused]] = 2, //  for 2D data e.g. texture u,v
    TINKER_3D [[maybe_unused]] = 3, //  for 3D data e.g. vertex positions
    TINKER_4D [[maybe_unused]] = 4, //  for 4D data
};

enum class TextureFilter {
    Nearest,  // Nearest-neighbor filtering
    Linear    // Linear interpolation filtering
};

enum class TextureWrap {
    Repeat,   // Repeat the texture
    Clamp     // Clamp texture coordinates to the edge
};