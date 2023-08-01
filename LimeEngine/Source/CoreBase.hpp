// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include <filesystem>
#include "Helpers/MacroUnility.hpp"
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
#define LE_LOG_PRESET_FULL
#define LE_ENABLE_ASSERTION
#define LE_ENABLE_IMGUI
#define LE_ENABLE_RENDER_API_DX11

#if defined(LE_ENABLE_RENDER_API_DX11)
	#define LE_ENABLE_COM
#endif

namespace LimeEngine
{
	using FPath = std::filesystem::path;
}

#include "Base/Debugger.hpp"
#include "Base/String.hpp"
#include "Base/StaticInitializer.hpp"
#include "Diagnostics/Logger.hpp"
#include "Diagnostics/RuntimeEditor.hpp"
#include "Base/Assert.hpp"
#include "Exceptions/EngineExceptions.hpp"
#include "Base/Transform.hpp"
