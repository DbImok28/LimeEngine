#pragma once
#include "GameResource.hpp"

namespace LimeEngine
{
	class GameDataLoader
	{
	public:
		GameResourceData LoadResource(const std::string& gamePath, const std::string& loadParams) const
		{
			static_assert("Not implemented");
			return GameResourceData(nullptr, 0);
		}
	};
}