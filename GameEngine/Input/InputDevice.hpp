#pragma once
#include "../Window/Window.hpp"
#include "Keyboard.hpp"

class InputDevice
{
	friend class Window;
private:
	LRESULT ProcInputMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
public:
	Keyboard keyboard;
};