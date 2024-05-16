// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CameraComponent.hpp"
#include "Base/Event.hpp"

namespace LimeEngine
{
	class DefaultPlayerCameraComponent : public CameraComponent
	{
	public:
		explicit DefaultPlayerCameraComponent(
			const std::string& componentName = "DefaultPlayerCameraComponent", float cameraMovementSpeed = 20.0f, float cameraRotationSpeed = 50.0f) noexcept;
		virtual ~DefaultPlayerCameraComponent();

		void MoveForward(float scale) noexcept;
		void MoveRight(float scale) noexcept;
		void MoveUp(float scale) noexcept;
		void TurnUp(float scale) noexcept;
		void TurnRight(float scale) noexcept;
		void OnResize(const Event& e);

		void AttachCamera() noexcept;

	protected:
		virtual void DebugUpdate() override;

		size_t id = 0;
		float cameraMovementSpeed;
		float cameraRotationSpeed;
	};
}