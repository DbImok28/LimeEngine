#include "InputDevice.hpp"

LRESULT InputDevice::ProcInputMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;

		// Keyboard
	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
	{
		unsigned char keycode = static_cast<unsigned char>(wParam);
		if (keyboard.IsKeysAutoRepeat())
		{
			keyboard.OnKeyPressed(keycode);
		}
		else
		{
			const bool wasPressed = lParam & 0x40000000;
			if (!wasPressed)
			{
				keyboard.OnKeyPressed(keycode);
			}
		}
		return 0;
	}
	case WM_SYSKEYUP:
	case WM_KEYUP:
	{
		keyboard.OnKeyReleased(static_cast<unsigned char>(wParam));
		return 0;
	}
	case WM_CHAR:
	{
		char ch = static_cast<char>(wParam);
		if (keyboard.IsCharsAutoRepeat())
		{
			keyboard.OnChar(ch);
		}
		else
		{
			const bool wasPressed = lParam & 0x40000000;
			if (!wasPressed)
			{
				keyboard.OnChar(ch);
			}
		}
		return 0;
	}
	case WM_KILLFOCUS:
		keyboard.ClearKeyState();
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
