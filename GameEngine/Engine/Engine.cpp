#include "Engine.hpp"

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
	static std::wostringstream ss;
	ss << "pos:"	<< window.graphics.camera->GetObjectLocation().x
		<< ",  "	<< window.graphics.camera->GetObjectLocation().y
		<< ",  "	<< window.graphics.camera->GetObjectLocation().z
		<< " rot:"	<< window.graphics.camera->GetObjectRotation().x * 360.0f / XM_2PI
		<< ",  "	<< window.graphics.camera->GetObjectRotation().y * 360.0f / XM_2PI
		<< ",  "	<< window.graphics.camera->GetObjectRotation().z * 360.0f / XM_2PI;

	window.SetTitle(ss.str());
	ss = std::wostringstream{};

	float cameraRotSpeed = 0.005f;
	while (!window.inputDevice.mouse.EventBufferIsEmpty())
	{
		auto e = window.inputDevice.mouse.ReadEvent();
		if (window.inputDevice.mouse.IsRightDown() && e.GetType() == Mouse::MouseEvent::EventType::RawMove)
		{
			window.graphics.camera->AddObjectRotation(e.GetPosY() * cameraRotSpeed, e.GetPosX() * cameraRotSpeed, 0.0f);
		}
	}
	if (window.inputDevice.keyboard.KeyIsPressed('X'))
	{
		window.graphics.camera->AddObjectRotation(0.5f * deltaTime, 0.0f, 0.0f);
	}
	if (window.inputDevice.keyboard.KeyIsPressed('Y'))
	{
		window.graphics.camera->AddObjectRotation(0.0f, 0.5f * deltaTime, 0.0f);
	}
	if (window.inputDevice.keyboard.KeyIsPressed('C'))
	{
		window.graphics.camera->AddObjectRotation(0.0f, 0.0f, 0.5f * deltaTime);
	}

	float cameraSpeed = 20.0f;
	if (window.inputDevice.keyboard.KeyIsPressed(VK_ESCAPE))
	{
		exit(0);
	}
	if (window.inputDevice.keyboard.KeyIsPressed('W'))
	{
		window.graphics.camera->AddObjectLocation(window.graphics.camera->GetObjectForwardVector() * cameraSpeed * deltaTime);
	}
	if (window.inputDevice.keyboard.KeyIsPressed('S'))
	{
		window.graphics.camera->AddObjectLocation(window.graphics.camera->GetObjectForwardVector() * -cameraSpeed * deltaTime);
	}
	if (window.inputDevice.keyboard.KeyIsPressed('A'))
	{
		window.graphics.camera->AddObjectLocation(window.graphics.camera->GetObjectRightVector() * -cameraSpeed * deltaTime);
	}
	if (window.inputDevice.keyboard.KeyIsPressed('D'))
	{
		window.graphics.camera->AddObjectLocation(window.graphics.camera->GetObjectRightVector() * cameraSpeed * deltaTime);
	}
	/*if (window.inputDevice.keyboard.KeyIsPressed('W'))
	{
		window.graphics.camera->AddObjectLocation(0.0f, cameraSpeed * deltaTime, 0.0f);
	}
	if (window.inputDevice.keyboard.KeyIsPressed('S'))
	{
		window.graphics.camera->AddObjectLocation(0.0f, -cameraSpeed * deltaTime, 0.0f);
	}
	if (window.inputDevice.keyboard.KeyIsPressed('A'))
	{
		window.graphics.camera->AddObjectLocation(-cameraSpeed * deltaTime, 0.0f, 0.0f);
	}
	if (window.inputDevice.keyboard.KeyIsPressed('D'))
	{
		window.graphics.camera->AddObjectLocation(cameraSpeed * deltaTime, 0.0f, 0.0f);
	}*/
	if (window.inputDevice.keyboard.KeyIsPressed(VK_SPACE))
	{
		window.graphics.camera->AddObjectLocation(0.0f, cameraSpeed * deltaTime, 0.0f);
	}
	if (window.inputDevice.keyboard.KeyIsPressed('Z'))
	{
		window.graphics.camera->AddObjectLocation(0.0f, -cameraSpeed * deltaTime, 0.0f);
	}
}

void Engine::RenderFrame()
{
	window.graphics.RenderFrame();
}