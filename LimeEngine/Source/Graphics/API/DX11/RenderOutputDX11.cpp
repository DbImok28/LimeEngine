// Developed by Pavel Jakushik.
// See LICENSE for copyright and licensing details (standard MIT License).
// GitHub https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "RendererDX11.hpp"
#include "RenderOutputDX11.hpp"

namespace LimeEngine
{
	WindowRenderOutputDX11::WindowRenderOutputDX11(RendererDX11& renderer, Window& window) : WindowRenderOutput(window), renderer(renderer) {}

	void WindowRenderOutputDX11::Init()
	{
		HRESULT hr;
		com_ptr<IDXGIFactory> pFactory;
		GFX_CHECK_HR_NOINFO(CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory.GetAddressOf())));

		// SwapChain
		DXGI_SWAP_CHAIN_DESC scd = { 0 };
		scd.BufferDesc.Width = window.GetWidth();
		scd.BufferDesc.Height = window.GetHeight();
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
		scd.Windowed = TRUE;
		scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		GFX_CHECK_HR(pFactory->CreateSwapChain(renderer.GetDevice(), &scd, swapchain.GetAddressOf()));

		// Extract output buffer
		GFX_CHECK_HR(swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf())));
	}

	void WindowRenderOutputDX11::Bind()
	{
		renderer.SetOutputBuffer(backBuffer.Get());
	}

	void WindowRenderOutputDX11::Present()
	{
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

	void WindowRenderOutputDX11::Resize(uint width, uint height)
	{
		renderer.Resize(width, height);
	}

	ID3D11Texture2D* WindowRenderOutputDX11::GetBackBuffer() const noexcept
	{
		return backBuffer.Get();
	}
}