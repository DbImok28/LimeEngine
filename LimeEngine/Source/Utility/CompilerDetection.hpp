// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once

#if defined(__clang__)
	#define LE_COMPILER_CLANG
#elif defined(__GNUC__) || defined(__GNUG__)
	#define LE_COMPILER_GCC
#elif defined(_MSC_VER)
	#define LE_COMPILER_MSVC
#endif
