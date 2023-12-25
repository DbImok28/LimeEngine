// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Utility/CompilerDetection.hpp"

#if defined(LE_COMPILER_CLANG)
	#define RESTRICT __restrict__
#elif defined(LE_COMPILER_GCC)
	#define RESTRICT __restrict
#elif defined(LE_COMPILER_MSVC)
	#define RESTRICT __restrict
#else
	#define RESTRICT
#endif