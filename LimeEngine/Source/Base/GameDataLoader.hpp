// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "GameResource.hpp"

namespace LimeEngine
{
	class GameDataLoader
	{
	public:
		GameResourceData LoadResource(const ResourcePath& resourcePath, const std::string& loadParams) const
		{
			static_assert("Not implemented");
			return GameResourceData(nullptr, 0);
		}
	};
}