#pragma once
#include "Graphics/Renderer.hpp"

namespace LimeEngine
{
	class RenderIO
	{
	public:
		explicit RenderIO(Renderer* renderer);
		std::optional<int> Process();
		void Render();

		Renderer* renderer = nullptr;
	};
}