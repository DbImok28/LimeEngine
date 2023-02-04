#pragma once
#include "Scene/CameraComponent.hpp"
#include "Window/Window.hpp"

namespace LimeEngine
{
	class RenderPreset
	{
	public:
		RenderPreset(CameraComponent* camera, Window* window) : camera(camera), window(window) {}

	public:
		CameraComponent* camera;
		Window* window;
	};
}
