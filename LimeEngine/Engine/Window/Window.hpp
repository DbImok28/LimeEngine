// Developed by Pavel Jakushik.
// See LICENSE for copyright and licensing details (standard MIT License).
// GitHub https://github.com/RubyCircle/LimeEngine
#pragma once
#include "WinApi.hpp"
#include <optional>
#include <string>
#include "../Input/InputDevice.hpp"

namespace LimeEngine
{
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
			static constexpr const wchar_t* name = L"LimeEngineWindow";
			static WindowClass wndClassInstance;
			HINSTANCE hInst;
		};

	public:
		Window(int width, int height, const wchar_t* title);
		~Window();
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		Window(Window&&) noexcept = delete;
		Window& operator=(Window&&) noexcept = delete;

		void SetTitle(const std::wstring& title);
		std::optional<int> ProcessMessages() noexcept;
		HWND GetHWnd() const noexcept;

	private:
		static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		static LRESULT CALLBACK HandleMsgForwarding(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

	public:
		int width;
		int height;
		InputDevice inputDevice;

	private:
		HWND hWnd;
	};
}