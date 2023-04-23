cmake_minimum_required(VERSION 3.20)
project(componentLayout)

set(VENDOR ${CMAKE_CURRENT_SOURCE_DIR}/vendor) # vendor folder
set(ENGINE ${CMAKE_CURRENT_SOURCE_DIR}/engine) # engine folder
set(CORE ${CMAKE_CURRENT_SOURCE_DIR}/core) # core folder
set(SANDBOX ${CMAKE_CURRENT_SOURCE_DIR}/sandbox) # sandbox folder
SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/vendor)

set(CMAKE_CXX_STANDARD 20)
#set(PHYSX_ROOT_DIR ${VENDOR}/physx)
#find_package(PhysX)

include_directories(
        "${VENDOR}/includes"
        "${VENDOR}/includes/physx"
)

link_directories(
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

#file(GLOB_RECURSE VENDOR_SOURCE_FILES
#        ${VENDOR}/*.cpp
#        ${VENDOR}/*.c
#        )

add_executable(componentLayout  ${ENGINE_HEADER_FILES} ${ENGINE_SOURCE_FILES} ${VENDOR_HEADER_FILES} ${VENDOR_SOURCE_FILES})
#target_link_options(componentLayout PUBLIC "/NODEFAULTLIB:library")

#Build and/or include libraries include lib files or build libs from .c files

add_library(glad ${VENDOR}/includes/glad/glad.c)

set(LIBS glfw3 glad opengl32 glad d3d11 DirectXTK)
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

target_link_libraries(componentLayout ${LIBS} ${PHYSX})

if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${VENDOR}/libs/debug/dll
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()