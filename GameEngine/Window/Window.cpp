#include <sstream>
#include <comdef.h>
#include "Window.hpp"
#include "resource.h"

Window::WindowClass Window::WindowClass::wndClassInstance;

Window::WindowClass::WindowClass() noexcept : hInst(GetModuleHandle(nullptr))
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIconW(hInst, LPWSTR(IDI_GAMEICON));
	wc.hIconSm = LoadIconW(hInst, LPWSTR(IDI_GAMEICON));
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = name;
	RegisterClassExW(&wc);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClassW(name, hInst);
}

const wchar_t* Window::WindowClass::GetName() noexcept
{
	return name;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
	return wndClassInstance.hInst;
}

Window::Window(const wchar_t* title, int width, int height): width(width), height(height)
{
	RECT wr;
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;
	if (AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE) == NULL)
		throw WND_LAST_EXCEPTION();

	hWnd = CreateWindowW(
		WindowClass::GetName(), title,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, 
		wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, WindowClass::GetInstance(), this
	);
	if(hWnd == nullptr)
		throw WND_LAST_EXCEPTION();
	ShowWindow(hWnd, SW_SHOWDEFAULT);
}

Window::~Window()
{
	DestroyWindow(hWnd);
}

void Window::SetTitle(const std::wstring& title)
{
	if (!SetWindowTextW(hWnd, title.c_str()))
		throw WND_LAST_EXCEPTION();
}

std::optional<int> Window::ProcessMessages() noexcept
{
	MSG msg;
	while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
		//PM_REMOVE Messages are removed from the queue after processing by PeekMessage.
	{
		if (msg.message == WM_QUIT)
			return static_cast<int>(msg.wParam);;
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return {};
}

LRESULT Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	// WM_NCCREATE - message when a window is first created.
	if (msg == WM_NCCREATE)
	{
		const CREATESTRUCTW* const pCreateStruct = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreateStruct->lpCreateParams);
		SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtrW(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgForwarding));
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK Window::HandleMsgForwarding(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}

Window::WindowException::WindowException(int line, const char* file, HRESULT hr) noexcept : EngineException(line, file), hr(hr) {}

const wchar_t* Window::WindowException::what() const noexcept
{
	_com_error errorInfo(hr);
	std::wostringstream oss;
	oss << GetType() << " - 0x" << std::hex << std::uppercase << hr << std::dec << L"(" << (unsigned long)hr << L")" << std::endl
		<< L"Description: " << errorInfo.ErrorMessage() << std::endl
		<< GetErrorLocation().c_str();
	buffer = oss.str();
	return buffer.c_str();
}

const wchar_t* Window::WindowException::GetType() const noexcept
{
	return L"WindowException";
}

HRESULT Window::WindowException::GetHr() const noexcept
{
	return hr;
}

std::wstring Window::WindowException::TranslateErrorCode(HRESULT hr) noexcept
{
	_com_error errorInfo(hr);
	return errorInfo.ErrorMessage();
}