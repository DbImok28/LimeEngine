// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "WindowsWindow.hpp"
#include "Engine.hpp"
#include "resource.h"

#ifdef LE_ENABLE_IMGUI
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
#endif

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

	WindowsWindow::WindowsWindow(const WindowArgs& args) : Window(MakeUnique<WindowsInput>())
	{
		Init(args);
	}

	WindowsWindow::~WindowsWindow()
	{
		Destroy();
	}

	void WindowsWindow::Init(const WindowArgs& args)
	{
		if (hWnd != nullptr) Destroy();

		width = args.width;
		height = args.height;
		name = args.name;
		title = args.title;

		styles = WS_SIZEBOX       // Sizing border
				 | WS_MAXIMIZEBOX // Maximize button
				 | WS_MINIMIZEBOX // Minimize button
				 | WS_CAPTION     // Title bar
				 | WS_SYSMENU;    // Menu in title bar

		RECT wr = { 0 };
		wr.left = 100;
		wr.right = static_cast<LONG>(width) + wr.left;
		wr.top = 100;
		wr.bottom = static_cast<LONG>(height) + wr.top;
		if (!AdjustWindowRect(&wr, static_cast<DWORD>(styles), FALSE)) throw WND_LAST_EXCEPTION();

		hWnd = CreateWindow(
			WindowClass::GetName(),
			title.c_str(),
			static_cast<DWORD>(styles),
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			wr.right - wr.left,
			wr.bottom - wr.top,
			nullptr,
			nullptr,
			WindowClass::GetInstance(),
			this);
		if (!hWnd) throw WND_LAST_EXCEPTION();

		exStyles = GetWindowLong(hWnd, GWL_EXSTYLE);
		ShowWindow(hWnd, SW_SHOWDEFAULT);

		static bool rawInputInitialized = false;
		if (!rawInputInitialized)
		{
			RAWINPUTDEVICE rid = { 0 };
			rid.usUsagePage = 0x01;
			rid.usUsage = 0x02;
			rid.dwFlags = 0;
			rid.hwndTarget = NULL;
			if (RegisterRawInputDevices(&rid, 1, sizeof(rid)) == FALSE) { throw WND_LAST_EXCEPTION(); }
			rawInputInitialized = true;
		}
	}

	void WindowsWindow::Destroy()
	{
		if (hWnd == nullptr) return;
		if (!DestroyWindow(hWnd)) { throw WND_LAST_EXCEPTION(); }
		hWnd = nullptr;
	}

	void WindowsWindow::OnUpdate()
	{
		MSG msg;
		while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
		// PM_REMOVE Messages are removed from the queue after processing by PeekMessage.
		{
			if (msg.message == WM_QUIT)
			{
				events(WindowEventType::Close, CloseWindowEvent(static_cast<int>(msg.wParam)));
				return;
			}
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}

	void WindowsWindow::UpdateCursor() const
	{
		if (!inSizeMoveMode && !hidden && ((GetClipCursorInFullScreenMode() && fullscreen) || GetClipCursorInWindowMode() && !fullscreen))
		{
			RECT windowRect = GetWindowRect();
			ClipCursor(&windowRect);
		}
		else { ClipCursor(NULL); }
	}

	void WindowsWindow::SetTitle(const tstring& newTitle)
	{
		title = newTitle;
		if (!SetWindowText(hWnd, title.c_str())) throw WND_LAST_EXCEPTION();
	}

	void WindowsWindow::SetFullscreen(bool fullscreen)
	{
		this->fullscreen = fullscreen;
		if (fullscreen)
		{
			savedWindowMaximized = maximized;
			if (maximized)
			{
				lockResizeEvent = true;
				::SendMessage(hWnd, WM_SYSCOMMAND, SC_RESTORE, 0);
				lockResizeEvent = false;
			}
			savedWindowSize = GetWindowRect();

			LONG newStyles = GetWindowLong(hWnd, GWL_STYLE);
			LONG newExStyles = GetWindowLong(hWnd, GWL_EXSTYLE);
			newStyles &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU);
			newExStyles &= ~(WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);
			SetWindowLong(hWnd, GWL_STYLE, newStyles);
			SetWindowLong(hWnd, GWL_EXSTYLE, newExStyles);

			auto screenRect = GetScreenRect();
			SetWindowPos(
				hWnd, HWND_TOP, screenRect.left, screenRect.top, screenRect.right - screenRect.left, screenRect.bottom - screenRect.top, SWP_FRAMECHANGED | SWP_SHOWWINDOW);
		}
		else
		{
			SetWindowLong(hWnd, GWL_STYLE, styles);
			SetWindowLong(hWnd, GWL_EXSTYLE, exStyles);

			if (savedWindowMaximized) { lockResizeEvent = true; }
			SetWindowPos(
				hWnd,
				HWND_NOTOPMOST,
				savedWindowSize.left,
				savedWindowSize.top,
				savedWindowSize.right - savedWindowSize.left,
				savedWindowSize.bottom - savedWindowSize.top,
				SWP_FRAMECHANGED | SWP_SHOWWINDOW);
			if (savedWindowMaximized)
			{
				lockResizeEvent = false;
				::SendMessage(hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
			}
		}
		UpdateCursor();
	}

	RECT WindowsWindow::GetWindowRect() const
	{
		RECT windowRect;
		::GetWindowRect(hWnd, &windowRect);
		return windowRect;
	}

	RECT WindowsWindow::GetScreenRect() const
	{
		HMONITOR monitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
		MONITORINFO info = { 0 };
		info.cbSize = sizeof MONITORINFO;
		CHECK_LAST_ERROR(GetMonitorInfo(monitor, &info));
		return info.rcMonitor;
	}

	std::pair<uint, uint> WindowsWindow::GetScreenResolution() const
	{
		auto screenRect = GetScreenRect();
		uint monitorWidth = static_cast<uint>(screenRect.right - screenRect.left);
		uint monitorHeight = static_cast<uint>(screenRect.bottom - screenRect.top);
		return { monitorWidth, monitorHeight };
	}

	void* WindowsWindow::GetHandle() const noexcept
	{
		return reinterpret_cast<void*>(hWnd);
	}

	LRESULT WindowsWindow::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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

	LRESULT CALLBACK WindowsWindow::HandleMsgForwarding(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		WindowsWindow* const pWindow = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		return pWindow->HandleMsg(hWnd, msg, wParam, lParam);
	}

	LRESULT WindowsWindow::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
#ifdef LE_ENABLE_IMGUI
		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)) return true;
#endif
		if (auto result = HandleWindowMsg(hWnd, msg, wParam, lParam); result) return *result;
		if (auto result = static_cast<WindowsInput&>(GetInput()).HandleInputMsg(hWnd, msg, wParam, lParam); result) return *result;
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	std::optional<LRESULT> WindowsWindow::HandleWindowMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
			case WM_CLOSE:
			{
				PostQuitMessage(0);
				return 0;
			}
			case WM_ENTERSIZEMOVE:
			{
				inSizeMoveMode = true;
				break;
			}
			case WM_EXITSIZEMOVE:
			{
				inSizeMoveMode = false;
				if (neadCallResizeEvent)
				{
					events(WindowEventType::Resize, ResizeWindowEvent(width, height));
					neadCallResizeEvent = false;
				}
				break;
			}
			case WM_SIZE:
			{
				width = std::max<uint>(static_cast<uint>(LOWORD(lParam)), 1u);
				height = std::max<uint>(static_cast<uint>(HIWORD(lParam)), 1u);
				switch (wParam)
				{
					case SIZE_MAXIMIZED:
					{
						maximized = true;
						hidden = false;
						break;
					}
					case SIZE_RESTORED:
					{
						maximized = false;
						hidden = false;
						break;
					}
					case SIZE_MINIMIZED:
					{
						hidden = true;
						break;
					}
				}
				if (inSizeMoveMode) { neadCallResizeEvent = true; }
				else if (!lockResizeEvent) { events(WindowEventType::Resize, ResizeWindowEvent(width, height)); }
				UpdateCursor();
				break;
			}
			case WM_MOVE:
			{
				const POINTS pt = MAKEPOINTS(lParam);
				posX = static_cast<int>(pt.x);
				posY = static_cast<int>(pt.y);
				break;
			}
			case WM_SETFOCUS:
			{
				UpdateCursor();
				events(WindowEventType::Focus, FocusWindowEvent(true));
				break;
			}
			case WM_KILLFOCUS:
			{
				events(WindowEventType::Focus, FocusWindowEvent(false));
				break;
			}
			case WM_SETCURSOR:
			{
				UpdateCursor();
				break;
			}
			case WM_SYSCOMMAND:
			{
				if (wParam == SC_KEYMENU) { return 0; }
				break;
			}
		}
		return std::nullopt;
	}
}