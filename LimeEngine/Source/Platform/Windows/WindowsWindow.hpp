// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Window/Window.hpp"
#include "WinApi.hpp"
#include "CoreBase.hpp"
#include "WindowsExceptions.hpp"
#include "WindowsInput.hpp"

namespace LimeEngine
{
	class WindowsWindow final : public Window
	{
	private:
		class WindowClass
		{
		public:
			WindowClass() noexcept;
			~WindowClass();

			static const TCHAR* GetName() noexcept;
			static HINSTANCE GetInstance() noexcept;

		private:
			static constexpr const TCHAR* name = TEXT("LimeEngineWindow");
			static WindowClass wndClassInstance;
			HINSTANCE hInst;
		};

	public:
		explicit WindowsWindow(const WindowArgs& args);
		virtual ~WindowsWindow();

	private:
		void Init(const WindowArgs& args);
		void Destroy();

	public:
		virtual void OnUpdate() override;
		virtual void UpdateCursor() const override;
		virtual void SetTitle(const tstring& title) override;
		virtual void SetFullsreen(bool bordered) override;
		virtual uint GetWidth() const noexcept override
		{
			return width;
		}
		virtual uint GetHeight() const noexcept override
		{
			return height;
		}
		virtual int GetPosX() const noexcept override
		{
			return posX;
		}
		virtual int GetPosY() const noexcept override
		{
			return posY;
		}
		RECT GetWindowRect() const;
		RECT GetScreenRect() const;
		virtual std::pair<uint, uint> GetScreenResolution() const override;
		virtual void* GetHandle() const noexcept override;

	private:
		static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK HandleMsgForwarding(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		std::optional<LRESULT> HandleWindowMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		uint width;
		uint height;
		int posX;
		int posY;
		bool hidden = false;
		bool maximized = false;

		LONG styles = 0;
		LONG exStyles = 0;

		RECT savedWindowSize = { 0 };
		bool savedWindowMaximized = false;
		bool lockResizeEvent = false;
		bool inSizeMoveMode = false;
		bool neadCallResizeEvent = false;

		HWND hWnd = nullptr;
	};
}