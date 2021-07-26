/*
* Copyright(C) 2021, by ѕавел якушик(ruby.circles774@gmail.com)
*/
#include "Window.hpp"

int APIENTRY wWinMain(
	_In_		HINSTANCE	hInstance,
	_In_opt_	HINSTANCE	hPrevInstance,
	_In_		LPWSTR		lpCmdLine,
	_In_		int			nCmdShow)
{
	
	Window window(L"GameEngine", 1080, 720);

	while (window.ProcessMessages());
	return 0;
}