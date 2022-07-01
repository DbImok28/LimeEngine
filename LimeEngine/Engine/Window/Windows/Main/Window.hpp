// Developed by Pavel Jakushik.
// See LICENSE for copyright and licensing details (standard MIT License).
// GitHub https://github.com/RubyCircle/LimeEngine
#pragma once
#include "../WinApi.hpp"
#include "../../../CoreBase.hpp"
#include "../../../Input/InputDevice.hpp"
#include <optional>

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

			static const TCHAR* GetName() noexcept;
			static HINSTANCE GetInstance() noexcept;

		private:
			static constexpr const TCHAR* name = TEXT("LimeEngineWindow");
			static WindowClass wndClassInstance;
			HINSTANCE hInst;
		};

	public:
		Window(int width, int height, const TCHAR* title);
		~Window();
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		Window(Window&&) noexcept = delete;
		Window& operator=(Window&&) noexcept = delete;

		void SetTitle(const tstring& title);
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