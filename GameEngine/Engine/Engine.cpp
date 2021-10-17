#include "Engine.hpp"

Engine::Engine(const wchar_t* windowTitle, int width, int height) : 
	window(this, windowTitle, width, height), 
	gameDataManager(this)
{
}

void Engine::Initialize()
{
	gameDataManager.StartupLoading();
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
	gameDataManager.Update();

	static std::wostringstream ss;
	ss << "pos:" << window.graphics.camera.GetComponentPosition().x
		<< ",  " << window.graphics.camera.GetComponentPosition().y
		<< ",  " << window.graphics.camera.GetComponentPosition().z
		<< " rot:" << window.graphics.camera.GetComponentRotation().x * 360.0f / XM_2PI
		<< ",  " << window.graphics.camera.GetComponentRotation().y * 360.0f / XM_2PI
		<< ",  " << window.graphics.camera.GetComponentRotation().z * 360.0f / XM_2PI;

	window.SetTitle(ss.str());
	ss = std::wostringstream{};

	float cameraRotSpeed = 0.005f;
	while (!window.inputDevice.mouse.EventBufferIsEmpty())
	{
		auto e = window.inputDevice.mouse.ReadEvent();
		if (window.inputDevice.mouse.IsRightDown() && e.GetType() == Mouse::MouseEvent::EventType::RawMove)
		{
			window.graphics.camera.AddComponentRotation(e.GetPosY() * cameraRotSpeed, e.GetPosX() * cameraRotSpeed, 0.0f);
		}
	}
	if (window.inputDevice.keyboard.KeyIsPressed('X'))
	{
		window.graphics.camera.AddComponentRotation(0.5f * deltaTime, 0.0f, 0.0f);
	}
	if (window.inputDevice.keyboard.KeyIsPressed('Y'))
	{
		window.graphics.camera.AddComponentRotation(0.0f, 0.5f * deltaTime, 0.0f);
	}
	if (window.inputDevice.keyboard.KeyIsPressed('C'))
	{
		window.graphics.camera.AddComponentRotation(0.0f, 0.0f, 0.5f * deltaTime);
	}

	float cameraSpeed = 20.0f;
	if (window.inputDevice.keyboard.KeyIsPressed(VK_ESCAPE))
	{
		exit(-1);
	}
	if (window.inputDevice.keyboard.KeyIsPressed('W'))
	{
		window.graphics.camera.AddComponentLocation(window.graphics.camera.GetComponentForwardVector() * cameraSpeed * deltaTime);
	}
	if (window.inputDevice.keyboard.KeyIsPressed('S'))
	{
		window.graphics.camera.AddComponentLocation(window.graphics.camera.GetComponentForwardVector() * -cameraSpeed * deltaTime);
	}
	if (window.inputDevice.keyboard.KeyIsPressed('A'))
	{
		window.graphics.camera.AddComponentLocation(window.graphics.camera.GetComponentRightVector() * -cameraSpeed * deltaTime);
	}
	if (window.inputDevice.keyboard.KeyIsPressed('D'))
	{
		window.graphics.camera.AddComponentLocation(window.graphics.camera.GetComponentRightVector() * cameraSpeed * deltaTime);
	}
	/*if (window.inputDevice.keyboard.KeyIsPressed('W'))
	{
		window.graphics.camera.AddComponentLocation(0.0f, cameraSpeed * deltaTime, 0.0f);
	}
	if (window.inputDevice.keyboard.KeyIsPressed('S'))
	{
		window.graphics.camera.AddComponentLocation(0.0f, -cameraSpeed * deltaTime, 0.0f);
	}
	if (window.inputDevice.keyboard.KeyIsPressed('A'))
	{
		window.graphics.camera.AddComponentLocation(-cameraSpeed * deltaTime, 0.0f, 0.0f);
	}
	if (window.inputDevice.keyboard.KeyIsPressed('D'))
	{
		window.graphics.camera.AddComponentLocation(cameraSpeed * deltaTime, 0.0f, 0.0f);
	}*/
	if (window.inputDevice.keyboard.KeyIsPressed(VK_SPACE))
	{
		window.graphics.camera.AddComponentLocation(0.0f, cameraSpeed * deltaTime, 0.0f);
	}
	if (window.inputDevice.keyboard.KeyIsPressed('Z'))
	{
		window.graphics.camera.AddComponentLocation(0.0f, -cameraSpeed * deltaTime, 0.0f);
	}
}

void Engine::RenderFrame()
{
	window.graphics.RenderFrame();
}