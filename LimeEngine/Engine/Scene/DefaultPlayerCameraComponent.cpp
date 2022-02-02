#include "DefaultPlayerCameraComponent.hpp"
#include "../Engine.hpp"

namespace LimeEngine
{
	DefaultPlayerCameraComponent::DefaultPlayerCameraComponent(Engine* engine, Transform transform, bool autoActivate, float cameraMovementSpeed, float cameraRotationSpeed) noexcept
		: CameraComponent(engine, transform, autoActivate, static_cast<float>(engine->window.width), static_cast<float>(engine->window.height)), cameraMovementSpeed(cameraMovementSpeed), cameraRotationSpeed(cameraRotationSpeed) {}

	void DefaultPlayerCameraComponent::Update()
	{
		CameraComponent::Update();

		float deltaTime = engine->deltaTime;
		auto& inputDevice = engine->window.inputDevice;
		while (!inputDevice.mouse.EventBufferIsEmpty())
		{
			auto e = inputDevice.mouse.ReadEvent();
			if (inputDevice.mouse.IsRightDown() && e.GetType() == Mouse::MouseEvent::EventType::RawMove)
			{
				AddRotation(e.GetPosY() * cameraRotationSpeed, e.GetPosX() * cameraRotationSpeed, 0.0f);
			}
		}
		if (inputDevice.keyboard.KeyIsPressed('W'))
		{
			AddLocation(GetForwardVector() * cameraMovementSpeed * deltaTime);
		}
		if (inputDevice.keyboard.KeyIsPressed('S'))
		{
			AddLocation(GetForwardVector() * -cameraMovementSpeed * deltaTime);
		}
		if (inputDevice.keyboard.KeyIsPressed('A'))
		{
			AddLocation(GetRightVector() * -cameraMovementSpeed * deltaTime);
		}
		if (inputDevice.keyboard.KeyIsPressed('D'))
		{
			AddLocation(GetRightVector() * cameraMovementSpeed * deltaTime);
		}
		if (inputDevice.keyboard.KeyIsPressed(VK_SPACE))
		{
			AddLocation(0.0f, cameraMovementSpeed * deltaTime, 0.0f);
		}
		if (inputDevice.keyboard.KeyIsPressed('Z'))
		{
			AddLocation(0.0f, -cameraMovementSpeed * deltaTime, 0.0f);
		}
	}
}