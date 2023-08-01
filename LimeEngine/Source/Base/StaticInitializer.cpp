// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "StaticInitializer.hpp"

namespace LimeEngine
{
	bool StaticInitializer::OrderFunctionsByPriority::operator()(std::pair<int8, std::function<void()>>& item1, std::pair<int8, std::function<void()>> item2)
	{
		return item1.first < item2.first;
	}

	auto& StaticInitializer::GetFunctionsForStaticInit()
	{
		static std::priority_queue<std::pair<int8, std::function<void()>>, std::vector<std::pair<int8, std::function<void()>>>, OrderFunctionsByPriority> functions = {};
		return functions;
	}

	uint8 StaticInitializer::Add(std::function<void()> func, int8 priority)
	{
		GetFunctionsForStaticInit().push(std::make_pair(priority, func));
		return 0;
	}

	void StaticInitializer::Initialize()
	{
		auto& functionsForInit = GetFunctionsForStaticInit();
		while (!functionsForInit.empty())
		{
			functionsForInit.top().second();
			functionsForInit.pop();
		}
	}
}
