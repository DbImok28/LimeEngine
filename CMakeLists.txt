# Copyright (C) Pavel Jakushik - All rights reserved
# See the LICENSE file for copyright and licensing details.
# GitHub: https://github.com/RubyCircle/LimeEngine

cmake_minimum_required(VERSION 3.20)

project("LimeEngine" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 23)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/Binaries/Any")
endif()

message(STATUS ${CMAKE_INSTALL_PREFIX})

add_subdirectory("LimeEngine")
add_subdirectory("Sandbox")
