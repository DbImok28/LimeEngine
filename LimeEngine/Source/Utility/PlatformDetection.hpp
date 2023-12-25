// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once

#ifdef _WIN32
	#ifdef _WIN64
		#define LE_BUILD_PLATFORM_WINDOWS
	#else
		#define LE_BUILD_PLATFORM_WINDOWS32
		#error "Windows x86 not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR
		#define LE_BUILD_PLATFORM_IOS_SIMULATOR
		#error "iOS simulator is not supported!"
	#elif TARGET_OS_IPHONE
		#define LE_BUILD_PLATFORM_IOS
		#error "iOS is not supported!"
	#elif TARGET_OS_MAC
		#define LE_BUILD_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
#elif defined(__ANDROID__)
	#define LE_BUILD_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define LE_BUILD_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	#error "Unknown platform!"
#endif