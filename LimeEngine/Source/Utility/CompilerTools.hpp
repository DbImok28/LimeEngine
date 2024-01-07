// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Utility/CompilerDetection.hpp"

#if defined(LE_COMPILER_CLANG)
	#define RESTRICT       __restrict__
	#define LE_FORCEINLINE inline
#elif defined(LE_COMPILER_GCC)
	#define RESTRICT       __restrict
	#define LE_FORCEINLINE inline
#elif defined(LE_COMPILER_MSVC)
	#define RESTRICT       __restrict
	#define LE_FORCEINLINE __forceinline
#else
	#define RESTRICT
	#define LE_FORCEINLINE inline
#endif
