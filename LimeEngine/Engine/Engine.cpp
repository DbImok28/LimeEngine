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
			if (exitCode = Processing())
				return *exitCode;
			RenderFrame();
		}
	}

	std::optional<int> Engine::Processing()
	{
		scene.UpdateScene();
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
		}
		else
		{
			window.SetTitle(L"Camera is not set");
		}
		if (window.inputDevice.keyboard.KeyIsPressed(VK_ESCAPE))
		{
			return 0;
		}
		return {};
	}

	void Engine::RenderFrame()
	{
		window.graphics.RenderFrame();
	}
}