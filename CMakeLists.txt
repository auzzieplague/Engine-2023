cmake_minimum_required(VERSION 3.20)
project(componentLayout)

set(VENDOR ${CMAKE_CURRENT_SOURCE_DIR}/vendor) # vendor folder
set(ENGINE ${CMAKE_CURRENT_SOURCE_DIR}/engine) # engine folder
set(CORE ${CMAKE_CURRENT_SOURCE_DIR}/core) # core folder
set(SANDBOX ${CMAKE_CURRENT_SOURCE_DIR}/sandbox) # sandbox folder

set(CMAKE_CXX_STANDARD 20)


include_directories(
        "${VENDOR}/includes"
)

link_directories(${VENDOR}/libs/debug)

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
        ${VENDOR}/Includes*.hpp
        ${VENDOR}/Includes*.h
        )

file(GLOB_RECURSE VENDOR_SOURCE_FILES
        ${VENDOR}/*.cpp
        ${VENDOR}/*.c
        )

add_executable(componentLayout  ${ENGINE_HEADER_FILES} ${ENGINE_SOURCE_FILES} ${VENDOR_HEADER_FILES} ${VENDOR_SOURCE_FILES})

#Build and/or include libraries include lib files or build libs from .c files

add_library(glad ${VENDOR}/includes/glad/glad.c)

set(LIBS glfw3 glad opengl32 glad d3d11 DirectXTK )

target_link_libraries(componentLayout ${LIBS})

if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${VENDOR}/libs
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()