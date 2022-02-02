#pragma once
#include "CameraComponent.hpp"

namespace LimeEngine
{
	class DefaultPlayerCameraComponent : public CameraComponent
	{
	public:
		DefaultPlayerCameraComponent(Engine* engine, Transform transform = {}, bool autoActivate = true, float cameraMovementSpeed = 20.0f, float cameraRotationSpeed = 0.4f) noexcept;
		void Update() override;
		float cameraMovementSpeed;
		float cameraRotationSpeed;
	};
}