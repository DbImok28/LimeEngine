#pragma once
#include "CameraComponent.hpp"

namespace LimeEngine
{
	class DefaultPlayerCameraComponent : public CameraComponent
	{
	public:
		explicit DefaultPlayerCameraComponent(
			Engine* engine, const Transform& transform = {}, size_t id = 0, float cameraMovementSpeed = 20.0f, float cameraRotationSpeed = 0.4f) noexcept;
		void MoveForward(float scale) noexcept;
		void MoveRight(float scale) noexcept;
		void MoveUp(float scale) noexcept;
		void TurnUp(float scale) noexcept;
		void TurnRight(float scale) noexcept;
		void Update() override;
		void AttachCamera() noexcept;
		void AttachCamera(size_t id) noexcept;

		size_t id = 0;
		float cameraMovementSpeed;
		float cameraRotationSpeed;
	};
}