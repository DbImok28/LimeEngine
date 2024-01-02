# Copyright (C) Pavel Jakushik - All rights reserved
# See the LICENSE file for copyright and licensing details.
# GitHub: https://github.com/RubyCircle/LimeEngine

cmake_minimum_required(VERSION 3.20)
include(../CMakeTools.cmake)

set(PROJECT_NAME LimeEngine)
project(${PROJECT_NAME} LANGUAGES CXX)
add_library(${PROJECT_NAME} SHARED)

set_target_properties(${TARGET} PROPERTIES
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    CXX_STANDARD 23
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
)

get_target_property(TARGET_TYPE ${PROJECT_NAME} TYPE)

# Compile shaders
set(RENDERER "DirectX")
set(SHADER_OUTPUT_DIR ${PROJECT_BINARY_DIR}/Shaders)
set(HLSL_VERTEX_SHADER
    VertexShader.hlsl
)
set(HLSL_PIXEL_SHADERS
    PixelShader.hlsl
)
CompileShaders()
DisableRTTI()

# Dependencies
set(${PROJECT_NAME}_DEPENDENCIES_INCLUDES
    PUBLIC
        # TODO: Move spdlog dependencies to PRIVATE
        ${PROJECT_SOURCE_DIR}/Dependencies/spdlog/include
    PRIVATE
        ${PROJECT_SOURCE_DIR}/Dependencies/DirectXTK/include
        ${PROJECT_SOURCE_DIR}/Dependencies/dxerr/include
        ${PROJECT_SOURCE_DIR}/Dependencies/imgui
        ${PROJECT_SOURCE_DIR}/Dependencies/imgui-notify/include
)
set(${PROJECT_NAME}_DEPENDENCIES_SOURCES
    ${PROJECT_SOURCE_DIR}/Dependencies/DirectXTK/include/DirectXTK/WICTextureLoader.cpp
    ${PROJECT_SOURCE_DIR}/Dependencies/DirectXTK/include/DirectXTK/DDSTextureLoader.cpp
    ${PROJECT_SOURCE_DIR}/Dependencies/dxerr/include/dxerr/dxerr.cpp
    ${PROJECT_SOURCE_DIR}/Dependencies/imgui/imgui.cpp
    ${PROJECT_SOURCE_DIR}/Dependencies/imgui/imgui_draw.cpp
    ${PROJECT_SOURCE_DIR}/Dependencies/imgui/imgui_tables.cpp
    ${PROJECT_SOURCE_DIR}/Dependencies/imgui/imgui_widgets.cpp
    ${PROJECT_SOURCE_DIR}/Dependencies/imgui/backends/imgui_impl_win32.cpp
    ${PROJECT_SOURCE_DIR}/Dependencies/imgui/backends/imgui_impl_dx11.cpp
    ${PROJECT_SOURCE_DIR}/Dependencies/imgui/misc/cpp/imgui_stdlib.cpp
)

# Resources
target_sources(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/Resource/LimeEngine.rc)

# Include
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Source>
    PRIVATE
        ${PROJECT_SOURCE_DIR}/Source
        ${CMAKE_CURRENT_SOURCE_DIR}/Resource
        ${${PROJECT_NAME}_DEPENDENCIES_INCLUDES}
)

target_precompile_headers(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Source/lepch.hpp)

# Sources
file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES 
    LIST_DIRECTORIES FALSE
    CONFIGURE_DEPENDS
    ${PROJECT_SOURCE_DIR}/Source/*.h
    ${PROJECT_SOURCE_DIR}/Source/*.hpp
    ${PROJECT_SOURCE_DIR}/Source/*.cpp
)
set(${PROJECT_NAME}_SOURCES
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_DEPENDENCIES_SOURCES}
)
source_group(
    TREE 
        ${PROJECT_SOURCE_DIR}
    FILES 
        ${${PROJECT_NAME}_SOURCES}
)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${${PROJECT_NAME}_SOURCES}
)

# Definitions
if(${TARGET_TYPE} STREQUAL "SHARED_LIBRARY")
    target_compile_definitions(${PROJECT_NAME} PUBLIC LE_BUILD_DYNAMIC_LINK PRIVATE LE_BUILD_DLL)
endif()

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
)

# Libs
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        d3d11.lib
        dxgi.lib
        D3DCompiler.lib
        dxguid.lib
)

install(TARGETS ${PROJECT_NAME} DESTINATION .)
InstallPDB()
install(DIRECTORY ${PROJECT_SOURCE_DIR}/Content DESTINATION .)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Shaders DESTINATION .)
