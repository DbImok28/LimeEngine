#include "lepch.hpp"
#include "DefaultPlayerCameraComponent.hpp"
#include "Engine.hpp"

namespace LimeEngine
{
	DefaultPlayerCameraComponent::DefaultPlayerCameraComponent(Engine* engine, const Transform& transform, float cameraMovementSpeed, float cameraRotationSpeed) noexcept :
		CameraComponent(engine, transform), cameraMovementSpeed(cameraMovementSpeed), cameraRotationSpeed(cameraRotationSpeed)
	{
		if (!engine->renderLayer.GetRenderCamera())
		{
			AttachCamera();
		}
		engine->windowLayer.GetWindow().events.Bind(WindowEventType::Resize, this, &DefaultPlayerCameraComponent::OnResize);

		auto& inputDevice = engine->inputLayer.GetInputDevice();
		inputDevice.BindAxisEvent("MoveForward", this, &DefaultPlayerCameraComponent::MoveForward);
		inputDevice.BindAxisEvent("MoveRight", this, &DefaultPlayerCameraComponent::MoveRight);
		inputDevice.BindAxisEvent("MoveUp", this, &DefaultPlayerCameraComponent::MoveUp);
		inputDevice.BindAxisEvent("TurnUp", this, &DefaultPlayerCameraComponent::TurnUp);
		inputDevice.BindAxisEvent("TurnRight", this, &DefaultPlayerCameraComponent::TurnRight);
	}

	DefaultPlayerCameraComponent::~DefaultPlayerCameraComponent()
	{
		engine->windowLayer.GetWindow().events.Unbind(WindowEventType::Resize, this, &DefaultPlayerCameraComponent::OnResize);

		auto& inputDevice = engine->inputLayer.GetInputDevice();
		inputDevice.UnbindAxisEvent("MoveForward", this, &DefaultPlayerCameraComponent::MoveForward);
		inputDevice.UnbindAxisEvent("MoveRight", this, &DefaultPlayerCameraComponent::MoveRight);
		inputDevice.UnbindAxisEvent("MoveUp", this, &DefaultPlayerCameraComponent::MoveUp);
		inputDevice.UnbindAxisEvent("TurnUp", this, &DefaultPlayerCameraComponent::TurnUp);
		inputDevice.UnbindAxisEvent("TurnRight", this, &DefaultPlayerCameraComponent::TurnRight);
	}

	void DefaultPlayerCameraComponent::MoveForward(float scale) noexcept
	{
		float deltaTime = engine->deltaTime;
		AddLocation(GetForwardVector() * (scale * cameraMovementSpeed * deltaTime));
	}

	void DefaultPlayerCameraComponent::MoveRight(float scale) noexcept
	{
		float deltaTime = engine->deltaTime;
		AddLocation(GetRightVector() * (scale * cameraMovementSpeed * deltaTime));
	}

	void DefaultPlayerCameraComponent::MoveUp(float scale) noexcept
	{
		float deltaTime = engine->deltaTime;
		AddLocation(0.0f, (scale * cameraMovementSpeed * deltaTime), 0.0f);
	}

	void DefaultPlayerCameraComponent::TurnUp(float scale) noexcept
	{
		if (engine->inputLayer.GetInputDevice().mouse.IsRightDown())
		{
			float deltaTime = engine->deltaTime;
			AddRotation(scale, 0.0f, 0.0f);
		}
	}

	void DefaultPlayerCameraComponent::TurnRight(float scale) noexcept
	{
		if (engine->inputLayer.GetInputDevice().mouse.IsRightDown())
		{
			float deltaTime = engine->deltaTime;
			AddRotation(0.0f, scale, 0.0f);
		}
	}

	void DefaultPlayerCameraComponent::OnResize(const Event& e)
	{
		auto& resizeEvent = CastEvent<ResizeWindowEvent>(e);
		Resize(resizeEvent.width, resizeEvent.height);
	}

	void DefaultPlayerCameraComponent::Update()
	{
		CameraComponent::Update();
	}

	void DefaultPlayerCameraComponent::AttachCamera() noexcept
	{
		engine->renderLayer.SetRenderCamera(this);

		auto& window = engine->windowLayer.GetWindow();
		width = static_cast<float>(window.GetWidth());
		height = static_cast<float>(window.GetHeight());
	}
}