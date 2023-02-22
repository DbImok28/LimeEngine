// Copyright (C) 2022 Pavel Jakushik - All Rights Reserved
// See file LICENSE for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Base/PlatformDetection.hpp"

#ifdef _DEBUG
	#define LE_DEBUG
#endif

#if defined(LE_BUILD_PLATFORM_WINDOWS)
	#ifdef LE_BUILD_DLL
		#define LE_API __declspec(dllexport)
	#else
		#define LE_API __declspec(dllimport)
	#endif
#else
	#error "Platform not supported!"
#endif

#ifdef LE_DEBUG
	#if defined(LE_BUILD_PLATFORM_WINDOWS)
		#define LE_DEBUGBREAK() __debugbreak()
	#elif defined(LE_BUILD_PLATFORM_LINUX)
		#include <signal.h>
		#define LE_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform does not support debugbreak!"
	#endif
#endif

#define LE_DELETE_COPY(ClassName)         \
	ClassName(const ClassName&) = delete; \
	ClassName& operator=(const ClassName&) = delete;

#define LE_DELETE_MOVE(ClassName)    \
	ClassName(ClassName&&) = delete; \
	ClassName& operator=(ClassName&&) = delete;

#define LE_DELETE_MOVE_COPY(ClassName) \
	LE_DELETE_COPY(ClassName)          \
	LE_DELETE_MOVE(ClassName)

#define LE_CONSOLE
#define LE_LOG_FULL
#define LE_ENABLE_ASSERTION
#define LE_ENABLE_IMGUI
#define LE_ENABLE_RENDER_API_DX11

#if defined(LE_ENABLE_RENDER_API_DX11)
	#define LE_ENABLE_COM
#endif

#include "Base/String.hpp"
#include "Base/Assert.hpp"
#include "Diagnostics/Logger.hpp"
#include "Diagnostics/RuntimeEditor.hpp"
#include "Exceptions/EngineExceptions.hpp"
#include "Base/Transform.hpp"
