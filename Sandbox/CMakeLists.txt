# Copyright (C) Pavel Jakushik - All rights reserved
# See the LICENSE file for copyright and licensing details.
# GitHub: https://github.com/RubyCircle/LimeEngine

cmake_minimum_required(VERSION 3.20)
include(../CMakeTools.cmake)

set(PROJECT_NAME Sandbox)
project(${PROJECT_NAME} LANGUAGES CXX)
add_executable(${PROJECT_NAME} WIN32)

set_target_properties(${TARGET} PROPERTIES
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        CXX_STANDARD 23
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
)

get_target_property(TARGET_TYPE ${PROJECT_NAME} TYPE)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

# Compile shaders
set(RENDERER "DirectX")
set(SHADER_OUTPUT_DIR ${PROJECT_BINARY_DIR}/Shaders)
set(HLSL_VERTEX_SHADER
        # ...
)
set(HLSL_PIXEL_SHADERS
        # ...
)
CompileShaders()
DisableRTTI()

# Dependencies
set(${PROJECT_NAME}_DEPENDENCIES_INCLUDES
        PUBLIC
        # ...
        PRIVATE
        # ...
)
set(${PROJECT_NAME}_DEPENDENCIES_SOURCES
        # ...
)

# Include
target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Source
        ${${PROJECT_NAME}_DEPENDENCIES_INCLUDES}
)

# Sources
file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES
        LIST_DIRECTORIES FALSE
        CONFIGURE_DEPENDS
        ${PROJECT_SOURCE_DIR}/Source/*.h
        ${PROJECT_SOURCE_DIR}/Source/*.hpp
        ${PROJECT_SOURCE_DIR}/Source/*.c
        ${PROJECT_SOURCE_DIR}/Source/*.cpp
)
set(${PROJECT_NAME}_SOURCES
        ${${PROJECT_NAME}_SOURCES}
        ${${PROJECT_NAME}_DEPENDENCIES_SOURCES}
)
source_group(TREE ${PROJECT_SOURCE_DIR}
        FILES
        ${${PROJECT_NAME}_SOURCES}
)
target_sources(${PROJECT_NAME}
        PRIVATE
        ${${PROJECT_NAME}_SOURCES}
)

# Definitions
target_compile_definitions(${PROJECT_NAME}
        PRIVATE
        # ...
)

# Libs
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        LimeEngine
)

# TODO: Add a config file to store the paths to the content and shader directories.
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/LimeEngine/Content
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/Content
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_BINARY_DIR}/LimeEngine/Shaders
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/Shaders
)

install(TARGETS ${PROJECT_NAME} DESTINATION .)
InstallPDB()
install(DIRECTORY ${PROJECT_SOURCE_DIR}/Content DESTINATION . OPTIONAL)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Shaders DESTINATION . OPTIONAL)
