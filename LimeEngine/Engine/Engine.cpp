#include "Engine.hpp"

namespace LimeEngine
{
	Engine::Engine(const wchar_t* windowTitle, int width, int height) :
		window(this, windowTitle, width, height),
		gameDataManager(this)
	{
	}

	void Engine::Initialize()
	{
		scene.Initialize(this);
	}

	int Engine::Start()
	{
		Initialize();
		timer.Start();
		std::optional<int> exitCode = 0;
		while (true)
		{
			deltaTime = timer.ElapsedTime();
			timer.Restart();
			if (exitCode = window.ProcessMessages())
				return *exitCode;

			Processing();
			RenderFrame();
		}
	}

	void Engine::Processing()
	{
		scene.Update();
		static std::wostringstream ss;
		ss << "pos:" << window.graphics.camera->GetLocation().x
			<< ",  " << window.graphics.camera->GetLocation().y
			<< ",  " << window.graphics.camera->GetLocation().z
			<< " rot:" << window.graphics.camera->GetRotation().roll
			<< ",  " << window.graphics.camera->GetRotation().pitch
			<< ",  " << window.graphics.camera->GetRotation().yaw;

		window.SetTitle(ss.str());
		ss = std::wostringstream{};

		float cameraRotSpeed = 0.4f;
		while (!window.inputDevice.mouse.EventBufferIsEmpty())
		{
			auto e = window.inputDevice.mouse.ReadEvent();
			if (window.inputDevice.mouse.IsRightDown() && e.GetType() == Mouse::MouseEvent::EventType::RawMove)
			{
				window.graphics.camera->AddRotation(e.GetPosY() * cameraRotSpeed, e.GetPosX() * cameraRotSpeed, 0.0f);
			}
		}
		if (window.inputDevice.keyboard.KeyIsPressed('X'))
		{
			window.graphics.camera->AddRotation(0.5f * deltaTime, 0.0f, 0.0f);
		}
		if (window.inputDevice.keyboard.KeyIsPressed('Y'))
		{
			window.graphics.camera->AddRotation(0.0f, 0.5f * deltaTime, 0.0f);
		}
		if (window.inputDevice.keyboard.KeyIsPressed('C'))
		{
			window.graphics.camera->AddRotation(0.0f, 0.0f, 0.5f * deltaTime);
		}

		float cameraSpeed = 20.0f;
		if (window.inputDevice.keyboard.KeyIsPressed(VK_ESCAPE))
		{
			exit(0);
		}
		if (window.inputDevice.keyboard.KeyIsPressed('W'))
		{
			window.graphics.camera->AddLocation(window.graphics.camera->GetForwardVector() * cameraSpeed * deltaTime);
		}
		if (window.inputDevice.keyboard.KeyIsPressed('S'))
		{
			window.graphics.camera->AddLocation(window.graphics.camera->GetForwardVector() * -cameraSpeed * deltaTime);
		}
		if (window.inputDevice.keyboard.KeyIsPressed('A'))
		{
			window.graphics.camera->AddLocation(window.graphics.camera->GetRightVector() * -cameraSpeed * deltaTime);
		}
		if (window.inputDevice.keyboard.KeyIsPressed('D'))
		{
			window.graphics.camera->AddLocation(window.graphics.camera->GetRightVector() * cameraSpeed * deltaTime);
		}
		/*if (window.inputDevice.keyboard.KeyIsPressed('W'))
		{
			window.graphics.camera->AddLocation(0.0f, cameraSpeed * deltaTime, 0.0f);
		}
		if (window.inputDevice.keyboard.KeyIsPressed('S'))
		{
			window.graphics.camera->AddLocation(0.0f, -cameraSpeed * deltaTime, 0.0f);
		}
		if (window.inputDevice.keyboard.KeyIsPressed('A'))
		{
			window.graphics.camera->AddLocation(-cameraSpeed * deltaTime, 0.0f, 0.0f);
		}
		if (window.inputDevice.keyboard.KeyIsPressed('D'))
		{
			window.graphics.camera->AddLocation(cameraSpeed * deltaTime, 0.0f, 0.0f);
		}*/
		if (window.inputDevice.keyboard.KeyIsPressed(VK_SPACE))
		{
			window.graphics.camera->AddLocation(0.0f, cameraSpeed * deltaTime, 0.0f);
		}
		if (window.inputDevice.keyboard.KeyIsPressed('Z'))
		{
			window.graphics.camera->AddLocation(0.0f, -cameraSpeed * deltaTime, 0.0f);
		}
	}

	void Engine::RenderFrame()
	{
		window.graphics.RenderFrame();
	}
}