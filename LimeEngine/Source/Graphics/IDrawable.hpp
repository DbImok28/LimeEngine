// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"

namespace LimeEngine
{
	class Renderer;

	struct IDrawable
	{
		virtual void Draw(Renderer& renderer) = 0;
		virtual float GetDistance(const Vector& target) noexcept = 0;
		virtual ~IDrawable() = default;
	};
}