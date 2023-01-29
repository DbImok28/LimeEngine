// Developed by Pavel Jakushik.
// See LICENSE for copyright and licensing details (standard MIT License).
// GitHub https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "WindowsWindow.hpp"
#include "Engine.hpp"
#include "Exceptions/WindowExceptions.hpp"
#include "resource.h"

#ifdef IMGUI
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
#endif // IMGUI

namespace LimeEngine
{
	WindowsWindow::WindowClass WindowsWindow::WindowClass::wndClassInstance;

	WindowsWindow::WindowClass::WindowClass() noexcept : hInst(GetModuleHandle(nullptr))
	{
		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = HandleMsgSetup;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInst;
		wc.hIcon = LoadIcon(hInst, LPTSTR(IDI_GAMEICON));
		wc.hIconSm = LoadIcon(hInst, LPTSTR(IDI_GAMEICON));
		wc.hCursor = nullptr;
		wc.hbrBackground = nullptr;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = name;
		RegisterClassEx(&wc);
	}

	WindowsWindow::WindowClass::~WindowClass()
	{
		UnregisterClass(name, hInst);
	}

	const TCHAR* WindowsWindow::WindowClass::GetName() noexcept
	{
		return name;
	}

	HINSTANCE WindowsWindow::WindowClass::GetInstance() noexcept
	{
		return wndClassInstance.hInst;
	}

	WindowsWindow::~WindowsWindow()
	{
		DestroyWindow(hWnd);
	}

	void WindowsWindow::Init(WindowArgs args)
	{
		width = args.width;
		height = args.height;

		RECT wr = { 0 };
		wr.left = 100;
		wr.right = width + wr.left;
		wr.top = 100;
		wr.bottom = height + wr.top;
		if (!AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE)) throw WND_LAST_EXCEPTION();

		hWnd = CreateWindow(
			WindowClass::GetName(),
			args.title.c_str(),
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			wr.right - wr.left,
			wr.bottom - wr.top,
			nullptr,
			nullptr,
			WindowClass::GetInstance(),
			this);
		if (!hWnd) throw WND_LAST_EXCEPTION();
		ShowWindow(hWnd, SW_SHOWDEFAULT);

		static bool rawInputInitialized = false;
		if (!rawInputInitialized)
		{
			RAWINPUTDEVICE rid = { 0 };
			rid.usUsagePage = 0x01;
			rid.usUsage = 0x02;
			rid.dwFlags = 0;
			rid.hwndTarget = NULL;
			if (RegisterRawInputDevices(&rid, 1, sizeof(rid)) == FALSE)
			{
				throw WND_LAST_EXCEPTION();
			}
			rawInputInitialized = true;
		}
	}

	void WindowsWindow::OnUpdate()
	{
		MSG msg;
		while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
		// PM_REMOVE Messages are removed from the queue after processing by PeekMessage.
		{
			if (msg.message == WM_QUIT)
			{
				CloseEvent(static_cast<int>(msg.wParam));
				return;
			}
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}

	void WindowsWindow::SetTitle(const tstring& title)
	{
		if (!SetWindowText(hWnd, title.c_str())) throw WND_LAST_EXCEPTION();
	}

	void* WindowsWindow::GetHandle() const noexcept
	{
		return reinterpret_cast<void*>(hWnd);
	}

	InputDevice& WindowsWindow::GetInputDevice() noexcept
	{
		return inputDevice;
	}

	LRESULT WindowsWindow::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
	{
		// WM_NCCREATE - message when a window is first created.
		if (msg == WM_NCCREATE)
		{
			const CREATESTRUCTW* const pCreateStruct = reinterpret_cast<CREATESTRUCTW*>(lParam);
			WindowsWindow* const pWindow = static_cast<WindowsWindow*>(pCreateStruct->lpCreateParams);
			if (!pWindow)
			{
				assert("Critical Error: pointer to Window is null!(Window::HandleMsgSetup)");
				exit(-1);
			}
			SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow)); // Set window ptr
			SetWindowLongPtrW(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&WindowsWindow::HandleMsgForwarding));
			return pWindow->HandleMsg(hWnd, msg, wParam, lParam);
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	LRESULT CALLBACK WindowsWindow::HandleMsgForwarding(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
	{
		WindowsWindow* const pWindow = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		return pWindow->HandleMsg(hWnd, msg, wParam, lParam);
	}

	LRESULT WindowsWindow::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
	{
#ifdef IMGUI
		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)) return true;
#endif // IMGUI

		switch (msg)
		{
			case WM_CLOSE:
				PostQuitMessage(0);
				return 0;
				// Keyboard
			case WM_SYSKEYDOWN:
			case WM_KEYDOWN:
			{
				auto key = static_cast<InputKey>(wParam);
				if (inputDevice.keyboard.IsKeysAutoRepeat())
				{
					inputDevice.OnKeyboardKeyPressed(key);
				}
				else
				{
					const bool wasPressed = lParam & 0x40000000;
					if (!wasPressed)
					{
						inputDevice.OnKeyboardKeyPressed(key);
					}
				}
				break;
			}
			case WM_SYSKEYUP:
			case WM_KEYUP:
			{
				inputDevice.OnKeyboardKeyReleased(static_cast<InputKey>(wParam));
				break;
			}
			case WM_CHAR:
			{
				char ch = static_cast<char>(wParam);
				if (inputDevice.keyboard.IsCharsAutoRepeat())
				{
					inputDevice.OnKeyboardChar(ch);
				}
				else
				{
					const bool wasPressed = lParam & 0x40000000;
					if (!wasPressed)
					{
						inputDevice.OnKeyboardChar(ch);
					}
				}
				break;
			}
			case WM_KILLFOCUS:
			{
				// TODO:Add kill focus event
				inputDevice.ClearKeyState();
				break;
			}
			// Mouse
			case WM_MOUSEMOVE:
			{
				const POINTS pt = MAKEPOINTS(lParam);
				inputDevice.OnMouseMove(pt.x, pt.y);
				if (pt.x >= 0 && pt.x < width && pt.y >= 0 && pt.y < height)
				{
					if (!inputDevice.mouse.IsInWindow())
					{
						SetCapture(hWnd);
						inputDevice.OnMouseEnter();
					}
				}
				else
				{
					if (inputDevice.mouse.IsInWindow())
					{
						ReleaseCapture();
						inputDevice.OnMouseLeave();
					}
				}
				break;
			}
			case WM_LBUTTONDOWN:
			{
				const POINTS pt = MAKEPOINTS(lParam);
				inputDevice.OnMouseLeftPressed(pt.x, pt.y);
				break;
			}
			case WM_RBUTTONDOWN:
			{
				const POINTS pt = MAKEPOINTS(lParam);
				inputDevice.OnMouseRightPressed(pt.x, pt.y);
				break;
			}
			case WM_MBUTTONDOWN:
			{
				const POINTS pt = MAKEPOINTS(lParam);
				inputDevice.OnMouseMiddlePressed(pt.x, pt.y);
				break;
			}
			case WM_LBUTTONUP:
			{
				const POINTS pt = MAKEPOINTS(lParam);
				inputDevice.OnMouseLeftReleased(pt.x, pt.y);
				break;
			}
			case WM_RBUTTONUP:
			{
				const POINTS pt = MAKEPOINTS(lParam);
				inputDevice.OnMouseRightReleased(pt.x, pt.y);
				break;
			}
			case WM_MBUTTONUP:
			{
				const POINTS pt = MAKEPOINTS(lParam);
				inputDevice.OnMouseMiddleReleased(pt.x, pt.y);
				break;
			}
			case WM_MOUSEWHEEL:
			{
				const POINTS pt = MAKEPOINTS(lParam);
				const int delta = GET_WHEEL_DELTA_WPARAM(wParam);
				inputDevice.OnMouseWheelDelta(pt.x, pt.y, delta);
				break;
			}
			case WM_INPUT:
			{
				UINT dataSize = 0u;
				GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER));
				if (dataSize > 0)
				{
					std::unique_ptr<BYTE[]> rawdata = std::make_unique<BYTE[]>(dataSize);
					if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, rawdata.get(), &dataSize, sizeof(RAWINPUTHEADER)) == dataSize)
					{
						RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(rawdata.get());
						if (raw->header.dwType == RIM_TYPEMOUSE)
						{
							inputDevice.OnMouseRawMove(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
						}
					}
				}
				break;
			}
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}