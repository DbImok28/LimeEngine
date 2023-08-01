// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include <functional>
#include <queue>
#include "CoreBase.hpp"

#define LE_STATIC_INITIALIZE(...)              LE_MACRO_OVERLOAD(LE_STATIC_INITIALIZE, __VA_ARGS__)
#define LE_STATIC_INITIALIZE_1(func)           static const inline ::LimeEngine::int8 _VarForStaticFunctionInit_##func = ::LimeEngine::StaticInitializer::Add(func)
#define LE_STATIC_INITIALIZE_2(func, priority) static const inline ::LimeEngine::int8 _VarForStaticFunctionInit_##func = ::LimeEngine::StaticInitializer::Add(func, priority)

namespace LimeEngine
{
	class StaticInitializer
	{
		struct OrderFunctionsByPriority
		{
			bool operator()(std::pair<int8, std::function<void()>>& item1, std::pair<int8, std::function<void()>> item2);
		};

	public:
		static auto& GetFunctionsForStaticInit();
		static uint8 Add(std::function<void()> func, int8 priority = 0);
		static void Initialize();
	};
}
