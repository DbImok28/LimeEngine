#include "Debugger.hpp"

#if defined(LE_BUILD_PLATFORM_LINUX)
	#include <signal.h>
#endif

namespace LimeEngine
{
	bool Debugger::IsDebuggerAttached() noexcept
	{
#if defined(LE_BUILD_PLATFORM_WINDOWS)
		return static_cast<bool>(IsDebuggerPresent());
#else
		LE_CORE_ASSERT(false, "Unknown platform. Failed to check debugger is attached!");
		return false;
#endif
	}
}