// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "Debugger.hpp"
#include "Platform/Platform.hpp"

namespace LimeEngine
{
	bool Debugger::IsDebuggerAttached() noexcept
	{
		return Platform::IsDebuggerAttached();
	}
}
