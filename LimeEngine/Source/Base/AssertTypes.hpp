// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"

namespace LimeEngine
{
	std::string GetErrnoMessage(errno_t errnoCode = errno);
}

#define LE_ASSERT_ERRNO(...)         LE_MACRO_OVERLOAD(LE_ASSERT_ERRNO, __VA_ARGS__)
#define LE_ASSERT_ERRNO_0()          LE_ASSERT(GetErrnoMessage(errno))
#define LE_ASSERT_ERRNO_1(errnoCode) LE_ASSERT(errnoCode != 0, GetErrnoMessage(errnoCode))
