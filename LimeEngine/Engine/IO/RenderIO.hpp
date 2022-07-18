#pragma once
#include "../Graphics/Renderer.hpp"

namespace LimeEngine
{
	class RenderIO
	{
	public:
		explicit RenderIO(Renderer* renderer);
		std::optional<int> Process();
		void Render(const CameraComponent* cameraComponent);

		Renderer* renderer = nullptr;
	};
}