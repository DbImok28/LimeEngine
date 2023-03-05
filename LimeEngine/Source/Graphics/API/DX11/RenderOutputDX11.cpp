// Developed by Pavel Jakushik.
// See LICENSE for copyright and licensing details (standard MIT License).
// GitHub https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "RendererDX11.hpp"
#include "RenderOutputDX11.hpp"

namespace LimeEngine
{
	WindowRenderOutputDX11::WindowRenderOutputDX11(RendererDX11& renderer, Window& window) : WindowRenderOutput(window), renderer(renderer) {}

	WindowRenderOutputDX11::~WindowRenderOutputDX11()
	{
		swapchain->SetFullscreenState(FALSE, NULL);
	}

	void WindowRenderOutputDX11::Init(DisplayMode mode)
	{
		LE_LOG_INFO("WindowRenderOutputDX11::Init");
		if (swapchain == nullptr)
		{
			com_ptr<IDXGIFactory> pFactory;
			GFX_CHECK_HR_NOINFO(CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory.GetAddressOf())));

			DXGI_SWAP_CHAIN_DESC scd = { 0 };

			scd.BufferDesc.Width = window.GetWidth();
			scd.BufferDesc.Height = window.GetHeight();
			scd.Windowed = TRUE;
			scd.BufferDesc.RefreshRate.Numerator = 60;
			scd.BufferDesc.RefreshRate.Denominator = 1;
			scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
			scd.SampleDesc.Count = 1;
			scd.SampleDesc.Quality = 0;
			scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			scd.BufferCount = 1;
			scd.OutputWindow = reinterpret_cast<HWND>(window.GetHandle());
			scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
			GFX_CHECK_HR(pFactory->CreateSwapChain(renderer.GetDevice(), &scd, swapchain.GetAddressOf()));
			backBuffer = nullptr;
		}
		if (backBuffer == nullptr)
		{
			GFX_CHECK_HR(swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf())));
		}
		SetDisplayMode(mode);
	}

	void WindowRenderOutputDX11::Bind()
	{
		LE_CORE_ASSERT((swapchain != nullptr) && (backBuffer != nullptr), "RenderOutput is not initialized");
		renderer.SetOutputBuffer(backBuffer.Get());
	}

	void WindowRenderOutputDX11::Present()
	{
		LE_CORE_ASSERT((swapchain != nullptr) && (backBuffer != nullptr), "RenderOutput is not initialized");
		HRESULT hr;
		GFX_ERROR_INFO;
		if (FAILED(hr = swapchain->Present(1, NULL)))
		{
			if (hr == DXGI_ERROR_DEVICE_REMOVED)
				throw GFX_EXCEPTION_HR(renderer.GetDevice()->GetDeviceRemovedReason());
			else
				throw GFX_EXCEPTION_HR(hr);
		}
	}

	void WindowRenderOutputDX11::Clear()
	{
		backBuffer.Reset();
	}

	void WindowRenderOutputDX11::Resize(uint width, uint height)
	{
		renderer.DestroyAllBuffers();
		GFX_CHECK_HR(swapchain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH));
		renderer.Resize(width, height);
	}

	void WindowRenderOutputDX11::SetDisplayMode(DisplayMode newMode)
	{
		if (displayMode != newMode)
		{
			if (newMode == DisplayMode::Windowed && displayMode == DisplayMode::FullscreenExclusive)
			{
				GFX_CHECK_HR(swapchain->SetFullscreenState(false, nullptr));
			}
			else if (newMode == DisplayMode::FullscreenExclusive)
			{
				GFX_CHECK_HR(swapchain->SetFullscreenState(true, nullptr));
			}
			displayMode = newMode;
		}
	}

	ID3D11Texture2D* WindowRenderOutputDX11::GetBackBuffer() const noexcept
	{
		return backBuffer.Get();
	}
}