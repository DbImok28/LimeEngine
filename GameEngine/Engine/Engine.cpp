#include "Engine.hpp"

Engine::Engine(const wchar_t* windowTitle, int width, int height) : window(windowTitle, width, height)
{
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
	static std::wostringstream ss;
	ss << "pos:" << window.GetGraphics().camera.GetObjectPosition().x
		<< ",  " << window.GetGraphics().camera.GetObjectPosition().y
		<< ",  " << window.GetGraphics().camera.GetObjectPosition().z
		<< " rot:" << window.GetGraphics().camera.GetObjectRotation().x * 360.0f / XM_2PI
		<< ",  " << window.GetGraphics().camera.GetObjectRotation().y * 360.0f / XM_2PI
		<< ",  " << window.GetGraphics().camera.GetObjectRotation().z * 360.0f / XM_2PI;

	window.SetTitle(ss.str());
	ss = std::wostringstream{};

	float cameraRotSpeed = 0.005f;
	while (!window.inputDevice.mouse.EventBufferIsEmpty())
	{
		auto e = window.inputDevice.mouse.ReadEvent();
		if (!window.inputDevice.keyboard.KeyIsPressed(VK_SHIFT) && e.GetType() == Mouse::MouseEvent::EventType::RawMove)
		{
			window.GetGraphics().camera.AddObjectRotation(e.GetPosY() * cameraRotSpeed, e.GetPosX() * cameraRotSpeed, 0.0f);
		}
	}
		if (window.inputDevice.keyboard.KeyIsPressed('X'))
		{
			window.GetGraphics().camera.AddObjectRotation(0.5f * deltaTime, 0.0f, 0.0f);
		}
		if (window.inputDevice.keyboard.KeyIsPressed('Y'))
		{
			window.GetGraphics().camera.AddObjectRotation(0.0f, 0.5f * deltaTime, 0.0f);
		}
		if (window.inputDevice.keyboard.KeyIsPressed('C'))
		{
			window.GetGraphics().camera.AddObjectRotation(0.0f, 0.0f, 0.5f * deltaTime);
		}

	float cameraSpeed = 20.0f;
	if (window.inputDevice.keyboard.KeyIsPressed(VK_ESCAPE))
	{
		exit(-1);
	}
	if (window.inputDevice.keyboard.KeyIsPressed('W'))
	{
		window.GetGraphics().camera.AddObjectLocation(window.GetGraphics().camera.GetObjectForwardVector() * cameraSpeed * deltaTime);
	}
	if (window.inputDevice.keyboard.KeyIsPressed('S'))
	{
		window.GetGraphics().camera.AddObjectLocation(window.GetGraphics().camera.GetObjectForwardVector() * -cameraSpeed * deltaTime);
	}
	if (window.inputDevice.keyboard.KeyIsPressed('A'))
	{
		window.GetGraphics().camera.AddObjectLocation(window.GetGraphics().camera.GetObjectRightVector() * -cameraSpeed * deltaTime);
	}
	if (window.inputDevice.keyboard.KeyIsPressed('D'))
	{
		window.GetGraphics().camera.AddObjectLocation(window.GetGraphics().camera.GetObjectRightVector() * cameraSpeed * deltaTime);
	}
	/*if (window.inputDevice.keyboard.KeyIsPressed('W'))
	{
		window.GetGraphics().camera.AddObjectLocation(0.0f, cameraSpeed * deltaTime, 0.0f);
	}
	if (window.inputDevice.keyboard.KeyIsPressed('S'))
	{
		window.GetGraphics().camera.AddObjectLocation(0.0f, -cameraSpeed * deltaTime, 0.0f);
	}
	if (window.inputDevice.keyboard.KeyIsPressed('A'))
	{
		window.GetGraphics().camera.AddObjectLocation(-cameraSpeed * deltaTime, 0.0f, 0.0f);
	}
	if (window.inputDevice.keyboard.KeyIsPressed('D'))
	{
		window.GetGraphics().camera.AddObjectLocation(cameraSpeed * deltaTime, 0.0f, 0.0f);
	}*/
	if (window.inputDevice.keyboard.KeyIsPressed(VK_SPACE))
	{
		window.GetGraphics().camera.AddObjectLocation(0.0f, cameraSpeed * deltaTime, 0.0f);
	}
	if (window.inputDevice.keyboard.KeyIsPressed('Z'))
	{
		window.GetGraphics().camera.AddObjectLocation(0.0f, -cameraSpeed * deltaTime, 0.0f);
	}
}

void Engine::RenderFrame()
{
	window.GetGraphics().RenderFrame();
}