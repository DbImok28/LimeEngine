#pragma once
#include "../../CoreBase.hpp"
#include "../Renderer.hpp"

namespace LimeEngine
{
	struct IDrawable
	{
		virtual void Draw(RenderingSystem& renderingSystem) = 0;
		virtual float GetDistance(const Vector& target) noexcept = 0;
	};
}