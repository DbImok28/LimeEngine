#include "lepch.hpp"
#include "DefaultPlayerCameraComponent.hpp"
#include "Engine.hpp"

namespace LimeEngine
{
	DefaultPlayerCameraComponent::DefaultPlayerCameraComponent(
		Engine* engine, const Transform& transform, unsigned Id, float cameraMovementSpeed, float cameraRotationSpeed) noexcept :
		CameraComponent(engine, transform),
		Id(Id), window(window), cameraMovementSpeed(cameraMovementSpeed), cameraRotationSpeed(cameraRotationSpeed)
	{
		if (!engine->engineIO[Id].sceneIO.camera)
		{
			AttachIO();
		}

		auto& inputDevice = window->GetInputDevice();
		inputDevice.BindAxisEvent("MoveForward", this, &DefaultPlayerCameraComponent::MoveForward);
		inputDevice.BindAxisEvent("MoveRight", this, &DefaultPlayerCameraComponent::MoveRight);
		inputDevice.BindAxisEvent("MoveUp", this, &DefaultPlayerCameraComponent::MoveUp);
		inputDevice.BindAxisEvent("TurnUp", this, &DefaultPlayerCameraComponent::TurnUp);
		inputDevice.BindAxisEvent("TurnRight", this, &DefaultPlayerCameraComponent::TurnRight);
	}

	void DefaultPlayerCameraComponent::MoveForward(float scale) noexcept
	{
		float deltaTime = engine->deltaTime;
		AddLocation(GetForwardVector() * scale * cameraMovementSpeed * deltaTime);
	}
	void DefaultPlayerCameraComponent::MoveRight(float scale) noexcept
	{
		float deltaTime = engine->deltaTime;
		AddLocation(GetRightVector() * scale * cameraMovementSpeed * deltaTime);
	}
	void DefaultPlayerCameraComponent::MoveUp(float scale) noexcept
	{
		float deltaTime = engine->deltaTime;
		AddLocation(0.0f, cameraMovementSpeed * scale * deltaTime, 0.0f);
	}
	void DefaultPlayerCameraComponent::TurnUp(float scale) noexcept
	{
		if (window->GetInputDevice().mouse.IsRightDown())
		{
			float deltaTime = engine->deltaTime;
			AddRotation(scale, 0.0f, 0.0f);
		}
	}
	void DefaultPlayerCameraComponent::TurnRight(float scale) noexcept
	{
		if (window->GetInputDevice().mouse.IsRightDown())
		{
			float deltaTime = engine->deltaTime;
			AddRotation(0.0f, scale, 0.0f);
		}
	}

	void DefaultPlayerCameraComponent::Update()
	{
		CameraComponent::Update();
	}
	void DefaultPlayerCameraComponent::AttachIO()
	{
		if (engine->engineIO.size() > Id)
		{
			window = engine->engineIO[Id].renderIO.renderer->GetWindow();
			width = static_cast<float>(window->GetWidth());
			height = static_cast<float>(window->GetHeight());
			engine->engineIO[Id].SetInputCamera(this);
		}
	}
	void DefaultPlayerCameraComponent::AttachIO(unsigned Id)
	{
		this->Id = Id;
		AttachIO();
	}
}