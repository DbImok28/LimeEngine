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