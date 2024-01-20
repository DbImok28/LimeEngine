// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Utility/CompilerDetection.hpp"

#if defined(LE_COMPILER_MSVC)
	#define LE_RESTRICT           __restrict
	#define LE_FORCEINLINE        __forceinline
	#define LE_DYNAMIC_LIB_EXPORT __declspec(dllexport)
	#define LE_DYNAMIC_LIB_IMPORT __declspec(dllimport)

#elif defined(LE_COMPILER_GCC)
	#define LE_RESTRICT           __restrict
	#define LE_FORCEINLINE        __attribute__((always_inline))
	#define LE_DYNAMIC_LIB_EXPORT __attribute__((visibility("default")))
	#define LE_DYNAMIC_LIB_IMPORT

#elif defined(LE_COMPILER_CLANG)
	#define LE_RESTRICT           __restrict__
	#define LE_FORCEINLINE        __attribute__((always_inline))
	#define LE_DYNAMIC_LIB_EXPORT __attribute__((visibility("default")))
	#define LE_DYNAMIC_LIB_IMPORT

#else
	#define LE_RESTRICT
	#define LE_FORCEINLINE inline
	#define LE_DYNAMIC_LIB_EXPORT
	#define LE_DYNAMIC_LIB_IMPORT
	#pragma warning Unknown compiler

#endif
