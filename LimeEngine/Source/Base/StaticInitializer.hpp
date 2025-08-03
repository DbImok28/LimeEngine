// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include <functional>
#include <queue>
#include "CoreBase.hpp"

#define LE_STATIC_INITIALIZE(...)              LE_MACRO_OVERLOAD(LE_STATIC_INITIALIZE, __VA_ARGS__)
#define LE_STATIC_INITIALIZE_1(func)           static const inline ::LimeEngine::uint8 _VarForStaticFunctionInit_##func = ::LimeEngine::StaticInitializer::Add(func)
#define LE_STATIC_INITIALIZE_2(func, priority) static const inline ::LimeEngine::uint8 _VarForStaticFunctionInit_##func = ::LimeEngine::StaticInitializer::Add(func, priority)
#define LE_STATIC_INITIALIZE_IMMEDIATE(func)                              \
	static inline ::LimeEngine::uint8 _FuncForStaticFunctionInit_##func() \
	{                                                                     \
		func();                                                           \
		return 0u;                                                        \
	}                                                                     \
	static const inline ::LimeEngine::uint8 _VarForStaticFunctionInit_##func = _FuncForStaticFunctionInit_##func()

namespace LimeEngine
{
	class LE_API StaticInitializer
	{
		struct OrderFunctionsByPriority
		{
			bool operator()(const std::pair<uint8, std::function<void()>>& item1, const std::pair<uint8, std::function<void()>>& item2) const;
		};

	public:
		static auto& GetFunctionsForStaticInit();
		static uint8 Add(const std::function<void()>& func, uint8 priority = StaticInitializer::DefaultPriority);
		static void Initialize();

		static constexpr uint8 DefaultPriority = 50u;
	};
}
