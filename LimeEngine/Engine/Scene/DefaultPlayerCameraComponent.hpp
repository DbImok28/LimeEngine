#pragma once
#include "../Window/Windows/Main/Window.hpp"
#include "CameraComponent.hpp"

namespace LimeEngine
{
	class DefaultPlayerCameraComponent : public CameraComponent
	{
	public:
		explicit DefaultPlayerCameraComponent(
			Engine* engine, const Transform& transform = {}, unsigned Id = 0, float cameraMovementSpeed = 20.0f, float cameraRotationSpeed = 0.4f) noexcept;
		void Update() override;
		void AttachIO();
		void AttachIO(unsigned Id);

		unsigned Id = 0;
		Window* window; //TODO: Remove Window
		float cameraMovementSpeed;
		float cameraRotationSpeed;
	};
}