// Developed by Pavel Jakushik.
// See LICENSE for copyright and licensing details (standard MIT License).
// GitHub https://github.com/RubyCircle/LimeEngine
#pragma once
extern std::unique_ptr<LimeEngine::Application> LimeEngine::CreateApplication();

#ifdef LE_BUILD_PLATFORM_WINDOWS
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
	using namespace LimeEngine;
	try
	{
		auto app = LimeEngine::CreateApplication();
		app->Run();

		return EXIT_SUCCESS;
	}
	catch (const EngineException& e)
	{
		MessageBoxA(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONERROR);
	}
	catch (const std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), "Standard exception", MB_OK | MB_ICONERROR);
	}
	catch (...)
	{
		MessageBoxA(nullptr, "No info", "Unknown exception", MB_OK | MB_ICONERROR);
	}
	return EXIT_FAILURE;
}
#endif
