// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Utility/PlatformDetection.hpp"
#include "Utility/CompilerDetection.hpp"
#include "Utility/CompilerTools.hpp"
#include "Utility/MacroUtility.hpp"
#include "Utility/ClassUtility.hpp"

#ifdef _DEBUG
	#define LE_DEBUG
#endif

#if defined(LE_BUILD_PLATFORM_WINDOWS)
	#if defined(LE_BUILD_DYNAMIC_LINK)
		#ifdef LE_BUILD_DLL
			#define LE_API __declspec(dllexport)
		#else
			#define LE_API __declspec(dllimport)
		#endif
	#else
		#define LE_API
	#endif
#else
	#error "Platform not supported!"
#endif

#include "StaticConfig.hpp"

#if defined(LE_ENABLE_RENDER_API_DX11)
	#define LE_ENABLE_COM
#endif

namespace std::filesystem
{
	class path;
}
namespace LimeEngine
{
	using FPath = std::filesystem::path;
}

#include "Base/Debugger.hpp"
#include "Base/BaseTypes.hpp"
#include "Base/StaticInitializer.hpp"
#include "Diagnostics/Logger.hpp"
#include "Diagnostics/RuntimeEditor.hpp"
#include "Base/Assert.hpp"
#include "Exceptions/EngineExceptions.hpp"
#include "Base/Transform.hpp"
