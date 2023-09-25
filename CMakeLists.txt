cmake_minimum_required(VERSION 3.20)
project(agnosticRendering)

set(VENDOR ${CMAKE_CURRENT_SOURCE_DIR}/vendor) # vendor folder
set(ENGINE ${CMAKE_CURRENT_SOURCE_DIR}/engine) # engine folder
set(CORE ${CMAKE_CURRENT_SOURCE_DIR}/core) # core folder
set(SANDBOX ${CMAKE_CURRENT_SOURCE_DIR}/sandbox) # sandbox folder
SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/vendor)

set(CMAKE_CXX_STANDARD 20)
#set(PHYSX_ROOT_DIR ${VENDOR}/physx)
#find_package(PhysX)

include_directories(
        "${VENDOR}"
        "${VENDOR}/includes"
        "${VENDOR}/includes/physx"
        "${VENDOR}/imgui/"

        "${ENGINE}/audio/"
        "${ENGINE}/input/"
        "${ENGINE}/loaders/"
        "${ENGINE}/networking/"
        "${ENGINE}/rendering/"
        "${ENGINE}/scene/"
        "${ENGINE}/scripting/"
        "${ENGINE}/ui/"

        "${ENGINE}/rendering/graphics/api/"

        "${CORE}/"
)

link_directories(
        ${VENDOR}/libs
        ${VENDOR}/libs/debug
        ${VENDOR}/libs/debug/physx
        )

file(GLOB_RECURSE ENGINE_HEADER_FILES
        ${CORE}/*.h
        ${ENGINE}/*.h
        )

file(GLOB_RECURSE ENGINE_SOURCE_FILES
        ${CORE}/*.cpp
        ${ENGINE}/*.cpp
        ${SANDBOX}/*.cpp
        )

file(GLOB_RECURSE VENDOR_HEADER_FILES
        ${VENDOR}/includes/*.hpp
        ${VENDOR}/includes/*.h
        )


#GUI
file(GLOB_RECURSE IMGUI_SOURCE_FILES ${VENDOR}/imgui/*.cpp)
file(GLOB_RECURSE IMGUI_HEADER_FILES ${VENDOR}/imgui/*.h)
add_library(imgui  ${IMGUI_HEADER_FILES} ${IMGUI_SOURCE_FILES})

#GUI
file(GLOB_RECURSE IMGUI_GIZMO_SOURCE_FILES ${VENDOR}/ImGuizmo/*.cpp)
file(GLOB_RECURSE IMGUI_GIZMO_HEADER_FILES ${VENDOR}/ImGuizmo/*.h)
add_library(imguizmo  ${IMGUI_GIZMO_HEADER_FILES} ${IMGUI_GIZMO_SOURCE_FILES})

#file(GLOB_RECURSE VENDOR_SOURCE_FILES
#        ${VENDOR}/*.cpp
#        ${VENDOR}/*.c
#        )

add_executable(agnosticRendering  ${ENGINE_HEADER_FILES} ${ENGINE_SOURCE_FILES} ${VENDOR_HEADER_FILES} ${VENDOR_SOURCE_FILES})
#target_link_options(agnosticRendering PUBLIC "/NODEFAULTLIB:library")

#Build and/or include libraries include lib files or build libs from .c files

add_library(glad ${VENDOR}/includes/glad/glad.c)

set(LIBS glfw3 glad opengl32
        imgui imguizmo
        d3d11 DirectXTK
        assimp)

set (PHYSX
        PhysX_32
        PhysXCommon_32
        PhysXCooking_32
        PhysXFoundation_32
        PhysXExtensions_static_32
        PhysXPvdSDK_static_32
#LowLevel_static_32
#LowLevelAABB_static_32
#LowLevelDynamics_static_32
#PhysXCharacterKinematic_static_32
#PhysXTask_static_32
#PhysXVehicle_static_32
#SceneQuery_static_32
#SimulationController_static_32
        )

target_link_libraries(agnosticRendering ${LIBS} ${PHYSX})

if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${VENDOR}/libs/debug/dll
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()
