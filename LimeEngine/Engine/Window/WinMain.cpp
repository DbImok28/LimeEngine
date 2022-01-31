// Developed by Pavel Jakushik. 
// See LICENSE for copyright and licensing details (standard MIT License).
// GitHub https://github.com/RubyCircle/LimeEngine
#include "../Engine.hpp"

int APIENTRY wWinMain(
	_In_		HINSTANCE	hInstance,
	_In_opt_	HINSTANCE	hPrevInstance,
	_In_		LPWSTR		lpCmdLine,
	_In_		int			nCmdShow)
{
	using namespace LimeEngine;
	try
	{
		HRESULT hr = CoInitialize(NULL);
		if (FAILED(hr))
			throw HR_EXCEPTION(hr);
		Engine engine;
		engine.Start();
		return EXIT_SUCCESS;
	}
	catch (const EngineException& e)
	{
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), "Standard exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBoxA(nullptr, "No info", "Unknown exception", MB_OK | MB_ICONEXCLAMATION);
	}
	return EXIT_FAILURE;
}