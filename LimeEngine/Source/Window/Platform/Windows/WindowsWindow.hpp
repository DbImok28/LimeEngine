// Developed by Pavel Jakushik.
// See LICENSE for copyright and licensing details (standard MIT License).
// GitHub https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Window/Base/Window.hpp"
#include "WinApi.hpp"
#include "CoreBase.hpp"

namespace LimeEngine
{
	class WindowsWindow : public Window
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
		WindowsWindow() = default;
		WindowsWindow(const WindowsWindow&) = delete;
		WindowsWindow& operator=(const WindowsWindow&) = delete;
		WindowsWindow(WindowsWindow&&) noexcept = delete;
		WindowsWindow& operator=(WindowsWindow&&) noexcept = delete;
		virtual ~WindowsWindow();

		void Init(WindowArgs args) override;
		void OnUpdate() override;
		void SetTitle(const tstring& title) override;
		uint GetWidth() const noexcept override
		{
			return width;
		}
		uint GetHeight() const noexcept override
		{
			return height;
		}
		void* GetHandle() const noexcept override;
		InputDevice& GetInputDevice() noexcept override;

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