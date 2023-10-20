#pragma once

#include <iostream>

// Determine the compiler and set the function signature macro accordingly
#if defined(__GNUC__) || defined(__clang__)
#define TINK_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
#define TINK_FUNC_SIG __FUNCSIG__
#else
#define TINK_FUNC_SIG "Unknown Function"
#endif

// Define the TINKER_MISSING_OVERRIDE macro
#define TINKER_MISSING_OVERRIDE std::cout << TINK_FUNC_SIG << " has no override function." << std::endl
