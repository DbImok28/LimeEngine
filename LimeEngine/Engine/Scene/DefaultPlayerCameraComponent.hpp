#pragma once
#include "../Window/Window.hpp"
#include "CameraComponent.hpp"

namespace LimeEngine
{
	class DefaultPlayerCameraComponent : public CameraComponent
	{
	public:
		DefaultPlayerCameraComponent(Engine* engine, Transform transform = {}, unsigned Id = 0, float cameraMovementSpeed = 20.0f, float cameraRotationSpeed = 0.4f) noexcept;
		void Update() override;
		void AttachIO();
		void AttachIO(unsigned Id);
		
		unsigned Id = 0;
		Window* window;
		float cameraMovementSpeed;
		float cameraRotationSpeed;
	};
}