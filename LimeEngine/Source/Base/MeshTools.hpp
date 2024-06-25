// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"

namespace LimeEngine
{
	constexpr std::vector<uint> ConvertTrianglesFormCWToCCW(const std::vector<uint>& cwTriangles) noexcept
	{
		std::vector<uint> ccwIndices(cwTriangles);
		for (size_t i = 1u; i < ccwIndices.size(); i += 3u)
		{
			std::swap(ccwIndices[i], ccwIndices[i + 1u]);
		}
		return ccwIndices;
	}

	constexpr std::vector<uint> ConvertTrianglesFormCCWToCW(const std::vector<uint>& ccwTriangles) noexcept
	{
		return ConvertTrianglesFormCWToCCW(ccwTriangles);
	}
}
