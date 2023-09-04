cmake_minimum_required(VERSION 3.20)
project(TinkerEngine)

set(CMAKE_CXX_STANDARD 20)

# Directories
set(VENDOR ${CMAKE_CURRENT_SOURCE_DIR}/vendor)
set(ENGINE ${CMAKE_CURRENT_SOURCE_DIR}/engine)
set(CORE ${CMAKE_CURRENT_SOURCE_DIR}/core)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "C:/src/lib")
# For shared libraries, uncomment the following line
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "C:/src/lib")

# Include and link directories
include_directories(
        "${VENDOR}"
        "${VENDOR}/includes"
        "${VENDOR}/includes/physx"
        "${VENDOR}/imgui/"
)

link_directories(
        ${VENDOR}/libs
        ${VENDOR}/libs/debug
        ${VENDOR}/libs/debug/physx
)

# Source files
file(GLOB_RECURSE ENGINE_HEADER_FILES ${CORE}/*.h ${ENGINE}/*.h)
file(GLOB_RECURSE ENGINE_SOURCE_FILES ${CORE}/*.cpp ${ENGINE}/*.cpp)

# Create the library
add_library(TinkerEngine STATIC ${ENGINE_HEADER_FILES} ${ENGINE_SOURCE_FILES})

# External Libraries
## GUI (imgui)
file(GLOB_RECURSE IMGUI_SOURCE_FILES ${VENDOR}/imgui/*.cpp)
file(GLOB_RECURSE IMGUI_HEADER_FILES ${VENDOR}/imgui/*.h)
add_library(imgui ${IMGUI_HEADER_FILES} ${IMGUI_SOURCE_FILES})

## PhysX
# Uncomment and modify this if you have a FindPhysX.cmake module
# find_package(PhysX)

# Libraries to link against
set(LIBS glfw3 glad opengl32 imgui d3d11 DirectXTK assimp)
set(PHYSX PhysX_32 PhysXCommon_32 PhysXCooking_32 PhysXFoundation_32 PhysXExtensions_static_32 PhysXPvdSDK_static_32)

# Linking
target_link_libraries(TinkerEngine PUBLIC ${LIBS} ${PHYSX})

# Expose include directories
target_include_directories(TinkerEngine PUBLIC ${CORE} ${ENGINE})
install(DIRECTORY ${CORE}/ DESTINATION "C:/src/headers" FILES_MATCHING PATTERN "*.h")
install(DIRECTORY ${ENGINE}/ DESTINATION "C:/src/headers" FILES_MATCHING PATTERN "*.h")