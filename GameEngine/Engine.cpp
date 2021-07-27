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
	static std::wstring str;
	str = std::to_wstring(deltaTime);
	window.SetTitle(str);
	str.clear();
}

void Engine::RenderFrame()
{
	window.gfx.RenderFrame();
}