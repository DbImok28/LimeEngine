#pragma once
#include "../Graphics/Renderer.hpp"

namespace LimeEngine
{
	class RenderIO
	{
	public:
		explicit RenderIO(Renderer* renderSystem);
		std::optional<int> Process();
		void Render(const CameraComponent* cameraComponent);

		Renderer* renderer = nullptr;
	};
}