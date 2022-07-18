#include "DefaultPlayerCameraComponent.hpp"
#include "../Engine.hpp"

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
	}

	void DefaultPlayerCameraComponent::Update()
	{
		CameraComponent::Update();

		if (!window) return;

		float deltaTime = engine->deltaTime;
		auto& inputDevice = window->inputDevice;
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
	void DefaultPlayerCameraComponent::AttachIO()
	{
		if (engine->engineIO.size() > Id)
		{
			window = engine->engineIO[Id].renderIO.renderer->window;
			width = static_cast<float>(window->width);
			height = static_cast<float>(window->height);
			engine->engineIO[Id].sceneIO.camera = this;
		}
	}
	void DefaultPlayerCameraComponent::AttachIO(unsigned Id)
	{
		this->Id = Id;
		AttachIO();
	}
}