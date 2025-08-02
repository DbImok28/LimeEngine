// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "StaticInitializer.hpp"

namespace LimeEngine
{
	bool StaticInitializer::OrderFunctionsByPriority::operator()(const std::pair<uint8, std::function<void()>>& item1, const std::pair<uint8, std::function<void()>>& item2) const
	{
		return item1.first < item2.first;
	}

	auto& StaticInitializer::GetFunctionsForStaticInit()
	{
		static std::priority_queue<std::pair<uint8, std::function<void()>>, std::vector<std::pair<uint8, std::function<void()>>>, OrderFunctionsByPriority> functions = {};
		return functions;
	}

	uint8 StaticInitializer::Add(const std::function<void()>& func, uint8 priority)
	{
		GetFunctionsForStaticInit().emplace(priority, func);
		return 0u;
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
