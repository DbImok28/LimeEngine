#include "Engine.hpp"

namespace LimeEngine
{
	Engine::Engine(const wchar_t* windowTitle, int width, int height) :
		window(this, windowTitle, width, height), gameDataManager(this), scene(this)
	{
		scene.Load();
	}

	int Engine::Start()
	{
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
		scene.UpdateScene();
		//TODO: Remove camera movement
		static std::wostringstream ss;
		if (scene.CameraIsSet())
		{
			auto camera = scene.GetCamera();
			ss << "pos:" << camera->GetLocation().x
				<< ",  " << camera->GetLocation().y
				<< ",  " << camera->GetLocation().z
				<< " rot:" << camera->GetRotation().roll
				<< ",  " << camera->GetRotation().pitch
				<< ",  " << camera->GetRotation().yaw;

			window.SetTitle(ss.str());
			ss = std::wostringstream{};

			float cameraRotSpeed = 0.4f;
			while (!window.inputDevice.mouse.EventBufferIsEmpty())
			{
				auto e = window.inputDevice.mouse.ReadEvent();
				if (window.inputDevice.mouse.IsRightDown() && e.GetType() == Mouse::MouseEvent::EventType::RawMove)
				{
					camera->AddRotation(e.GetPosY() * cameraRotSpeed, e.GetPosX() * cameraRotSpeed, 0.0f);
				}
			}
			if (window.inputDevice.keyboard.KeyIsPressed('X'))
			{
				camera->AddRotation(0.5f * deltaTime, 0.0f, 0.0f);
			}
			if (window.inputDevice.keyboard.KeyIsPressed('Y'))
			{
				camera->AddRotation(0.0f, 0.5f * deltaTime, 0.0f);
			}
			if (window.inputDevice.keyboard.KeyIsPressed('C'))
			{
				camera->AddRotation(0.0f, 0.0f, 0.5f * deltaTime);
			}

			float cameraSpeed = 20.0f;
			if (window.inputDevice.keyboard.KeyIsPressed(VK_ESCAPE))
			{
				exit(0);
			}
			if (window.inputDevice.keyboard.KeyIsPressed('W'))
			{
				camera->AddLocation(camera->GetForwardVector() * cameraSpeed * deltaTime);
			}
			if (window.inputDevice.keyboard.KeyIsPressed('S'))
			{
				camera->AddLocation(camera->GetForwardVector() * -cameraSpeed * deltaTime);
			}
			if (window.inputDevice.keyboard.KeyIsPressed('A'))
			{
				camera->AddLocation(camera->GetRightVector() * -cameraSpeed * deltaTime);
			}
			if (window.inputDevice.keyboard.KeyIsPressed('D'))
			{
				camera->AddLocation(camera->GetRightVector() * cameraSpeed * deltaTime);
			}
			/*if (window.inputDevice.keyboard.KeyIsPressed('W'))
			{
				camera->AddLocation(0.0f, cameraSpeed * deltaTime, 0.0f);
			}
			if (window.inputDevice.keyboard.KeyIsPressed('S'))
			{
				camera->AddLocation(0.0f, -cameraSpeed * deltaTime, 0.0f);
			}
			if (window.inputDevice.keyboard.KeyIsPressed('A'))
			{
				camera->AddLocation(-cameraSpeed * deltaTime, 0.0f, 0.0f);
			}
			if (window.inputDevice.keyboard.KeyIsPressed('D'))
			{
				camera->AddLocation(cameraSpeed * deltaTime, 0.0f, 0.0f);
			}*/
			if (window.inputDevice.keyboard.KeyIsPressed(VK_SPACE))
			{
				camera->AddLocation(0.0f, cameraSpeed * deltaTime, 0.0f);
			}
			if (window.inputDevice.keyboard.KeyIsPressed('Z'))
			{
				camera->AddLocation(0.0f, -cameraSpeed * deltaTime, 0.0f);
			}
		}
		else
		{
			window.SetTitle(L"Camera is not set");
		}
	}

	void Engine::RenderFrame()
	{
		window.graphics.RenderFrame();
	}
}