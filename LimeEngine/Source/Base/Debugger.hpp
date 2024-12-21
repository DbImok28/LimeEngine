// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"

#ifdef LE_DEBUG
	#if defined(LE_BUILD_PLATFORM_WINDOWS)
		#define LE_DEBUGBREAK() (__nop(), __debugbreak())
	#elif defined(LE_BUILD_PLATFORM_LINUX)
		#include <signal.h>
		#define LE_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform does not support debugbreak!"
	#endif
#else
	#define LE_DEBUGBREAK()
#endif

namespace LimeEngine
{
	class Debugger
	{
		Debugger() = delete;

	public:
		static bool IsDebuggerAttached() noexcept;
	};
}
