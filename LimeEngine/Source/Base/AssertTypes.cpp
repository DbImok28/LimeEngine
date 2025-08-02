// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "AssertTypes.hpp"

namespace LimeEngine
{
	std::string GetErrnoMessage(errno_t errnoCode)
	{
		char buf[256] = { '\0' };

#if defined(LE_BUILD_PLATFORM_WINDOWS)
		if (strerror_s(buf, sizeof(buf), errnoCode) == 0) { return std::string(buf); }
		else { return "Unknown error"; }
#else
	// POSIX strerror_r
	#if ((_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600) && !_GNU_SOURCE)
		// XSI-compliant strerror_r
		if (strerror_r(errnoCode, buf, sizeof(buf)) == 0) { return std::string(buf); }
		else { return "Unknown error"; }
	#else
		// GNU-specific strerror_r
		char* msg = strerror_r(errnoCode, buf, sizeof(buf));
		if (msg != nullptr) { return std::string(msg); }
		else { return "Unknown error"; }
	#endif
#endif
	}
}
