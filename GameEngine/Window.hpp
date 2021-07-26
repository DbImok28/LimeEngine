#pragma once
#include <string>
#include <Windows.h>

class Window
{
private:
	class WindowClass
	{
	public:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass(WindowClass&&) noexcept = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		WindowClass& operator=(WindowClass&&) noexcept = delete;

		static const wchar_t* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		static constexpr const wchar_t* name = L"GameEngineWindow";
		static WindowClass wndClassInstance;
		HINSTANCE hInst;
	};
public:
	Window(const wchar_t* title = L"GameEngine", int width = 1080, int height = 720);
	~Window();
	Window(const Window&) = delete;
	Window(Window&&) noexcept = delete;
	Window& operator=(const Window&) = delete;
	Window& operator=(Window&&) noexcept = delete;

	void SetTitle(const std::wstring& title);
	bool ProcessMessages() noexcept;
private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgForwarding(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

	int width;
	int height;
	HWND hWnd;
};