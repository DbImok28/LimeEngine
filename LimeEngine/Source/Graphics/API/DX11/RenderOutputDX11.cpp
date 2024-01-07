// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "RendererDX11.hpp"
#include "RenderOutputDX11.hpp"

namespace LimeEngine
{
	WindowRenderOutputDX11::WindowRenderOutputDX11(RendererDX11& renderer, Window& window, bool defaultFullscreenModeIsExclusive) :
		WindowRenderOutput(window, defaultFullscreenModeIsExclusive), renderer(renderer)
	{
		auto& inputDevice = GetWindow().GetInputDevice();
		inputDevice.AddActionMapping(
			"Engine.ResizeWindow",
			{
				{InputKey::Enter, true, false, false, false}
        });
		inputDevice.BindActionEvent("Engine.ResizeWindow", InputActionType::Pressed, this, &WindowRenderOutputDX11::OnResizeActionEvent);
	}

	WindowRenderOutputDX11::~WindowRenderOutputDX11()
	{
		GetWindow().GetInputDevice().UnbindActionEvent("Engine.ResizeWindow", InputActionType::Pressed, this, &WindowRenderOutputDX11::OnResizeActionEvent);
		if (displayMode == DisplayMode::FullscreenExclusive)
		{
			swapchain->SetFullscreenState(FALSE, NULL);
		}
	}

	void WindowRenderOutputDX11::Init()
	{
		if (swapchain == nullptr)
		{
			renderer.context.CreateSwapChain(swapchain.GetAddressOf(), window.GetHandle(), refreshRate);
			renderer.context.MakeWindowAssociation(window.GetHandle());
			backBuffer = nullptr;
		}
		if (backBuffer == nullptr)
		{
			GFX_CHECK_HR(swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf())));
		}
	}

	void WindowRenderOutputDX11::Bind()
	{
		LE_CORE_ASSERT((swapchain != nullptr) && (backBuffer != nullptr), "RenderOutput is not initialized");
		renderer.context.SetOutputBuffer(backBuffer.Get());
	}

	void WindowRenderOutputDX11::Present()
	{
		LE_CORE_ASSERT((swapchain != nullptr) && (backBuffer != nullptr), "RenderOutput is not initialized");
		HRESULT hr;
		GFX_ERROR_INFO;
		if (FAILED(hr = swapchain->Present(1, NULL)))
		{
			if (hr == DXGI_ERROR_DEVICE_REMOVED)
				throw GFX_EXCEPTION_HR(renderer.context.GetDevice()->GetDeviceRemovedReason());
			else
				throw GFX_EXCEPTION_HR(hr);
		}
	}

	void WindowRenderOutputDX11::Destroy()
	{
		backBuffer.Reset();
	}

	void WindowRenderOutputDX11::Resize(uint width, uint height)
	{
		DXGI_MODE_DESC BufferDesc = { 0 };
		BufferDesc.Width = width;
		BufferDesc.Height = height;
		BufferDesc.RefreshRate.Numerator = refreshRate;
		BufferDesc.RefreshRate.Denominator = 1;
		BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		GFX_CHECK_HR(swapchain->ResizeTarget(&BufferDesc));
	}

	void WindowRenderOutputDX11::OnResize(uint width, uint height)
	{
		LE_CORE_ASSERT(swapchain != nullptr, "Swapchain is not initialized");
		BOOL currentFullscreen = TRUE;
		GFX_CHECK_HR(swapchain->GetFullscreenState(&currentFullscreen, nullptr));
		if (currentFullscreen)
		{
			displayMode = DisplayMode::FullscreenExclusive;
		}
		renderer.DestroyAllBuffers();
		GFX_CHECK_HR(swapchain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH));
		renderer.Resize(width, height);
	}

	void WindowRenderOutputDX11::SetDisplayMode(DisplayMode newMode)
	{
		if (displayMode == newMode) return;

		switch (newMode)
		{
			case LimeEngine::DisplayMode::Windowed:
			{
				if (displayMode == DisplayMode::FullscreenExclusive)
				{
					GFX_CHECK_HR(swapchain->SetFullscreenState(false, nullptr));
				}
				window.SetFullsreen(false);
			}
			break;
			case LimeEngine::DisplayMode::FullscreenExclusive:
			{
				window.SetFullsreen(true);
				auto hr = swapchain->SetFullscreenState(true, nullptr);
				if (hr == DXGI_ERROR_NOT_CURRENTLY_AVAILABLE)
				{
					LE_CORE_ASSERT(false, "Switching to full screen mode is not currently available");
					window.SetFullsreen(false);
					return;
				}
				GFX_CHECK_HR(hr);
				window.UpdateCursor();
			}
			break;
			case LimeEngine::DisplayMode::FullscreenWindowed:
			{
				window.SetFullsreen(true);
			}
			break;
			default:
			{
				LE_CORE_ASSERT(false, "Unsupported window mode");
			}
		}
		displayMode = newMode;
	}

	void WindowRenderOutputDX11::OnResizeActionEvent()
	{
		if (displayMode != DisplayMode::Windowed)
		{
			SetDisplayMode(DisplayMode::Windowed);
		}
		else
		{
			if (defaultFullscreenModeIsExclusive)
			{
				SetDisplayMode(DisplayMode::FullscreenExclusive);
			}
			else
			{
				SetDisplayMode(DisplayMode::FullscreenWindowed);
			}
		}
	}

	ID3D11Texture2D* WindowRenderOutputDX11::GetBackBuffer() const noexcept
	{
		return backBuffer.Get();
	}
}
