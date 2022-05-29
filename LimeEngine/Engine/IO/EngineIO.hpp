#pragma once
#include "RenderIO.hpp"
#include "SceneIO.hpp"

namespace LimeEngine
{
	class EngineIO
	{
	public:
		EngineIO(RenderIO&& renderIO, SceneIO&& sceneIO);
		std::optional<int> Process();
		void Render();

		InputDevice& GetInput() noexcept;

		RenderIO renderIO;
		SceneIO sceneIO;
	};
}