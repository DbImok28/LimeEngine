/*
* Copyright(C) 2021, by ѕавел якушик(ruby.circles774@gmail.com)
*/
#include "../Engine.hpp"
int APIENTRY wWinMain(
	_In_		HINSTANCE	hInstance,
	_In_opt_	HINSTANCE	hPrevInstance,
	_In_		LPWSTR		lpCmdLine,
	_In_		int			nCmdShow)
{
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