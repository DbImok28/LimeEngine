#pragma once
#include <Windows.h>
#include "../Exceptions/EngineExceptions.hpp"

#define WND_EXCEPTION(hr) Window::WindowException(__LINE__, __FILE__, hr)
#define WND_LAST_EXCEPTION() Window::WindowException(__LINE__, __FILE__, GetLastError())

class Window
{
public:
	class WindowException : public EngineException
	{
	public:
		WindowException(int line, const char* file, HRESULT hr) noexcept;
		const wchar_t* what() const noexcept override;
		virtual const wchar_t* GetType() const noexcept;
		HRESULT GetHr() const noexcept;
		std::wstring TranslateErrorCode(HRESULT hr) noexcept;
	private:
		HRESULT hr;
	};
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