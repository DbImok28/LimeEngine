#pragma once
#include "Graphics/Renderer.hpp"

namespace LimeEngine
{
	class RenderIO
	{
	public:
		explicit RenderIO(Renderer* renderer);
		void Process();
		void Render();

		Renderer* renderer = nullptr;
	};
}