// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "RenderStatesDX11.hpp"
#include "RenderAPIDX11.hpp"
#include "RenderTargetDX11.hpp"

namespace LimeEngine
{
	////////////////////////////////// DepthStencilDX11

	DepthStencilDX11::DepthStencilDX11(uint width, uint height)
	{
		Initialize(width, height);
	}

	void DepthStencilDX11::Initialize(uint width, uint height)
	{
		if (depthStencilTextureView || depthStencilTexture)
		{
			depthStencilTextureView.Reset();
			depthStencilTexture.Reset();
		}

		D3D11_TEXTURE2D_DESC depthStencilDesc = { 0 };
		depthStencilDesc.Width = width;
		depthStencilDesc.Height = height;
		depthStencilDesc.MipLevels = 1u;
		depthStencilDesc.ArraySize = 1u;
		depthStencilDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.SampleDesc.Count = 1u;
		depthStencilDesc.SampleDesc.Quality = 0u;
		depthStencilDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0u;
		depthStencilDesc.MiscFlags = 0u;

		auto device = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDevice();
		GFX_CHECK_HR(device->CreateTexture2D(&depthStencilDesc, NULL, depthStencilTexture.GetAddressOf()));
		GFX_CHECK_HR(device->CreateDepthStencilView(depthStencilTexture.Get(), NULL, depthStencilTextureView.GetAddressOf()));
	}

	void DepthStencilDX11::Clear(float clearDepth, uint8 clearStencil)
	{
		auto deviceContext = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDeviceContext();
		deviceContext->ClearDepthStencilView(depthStencilTextureView.Get(), D3D11_CLEAR_FLAG::D3D11_CLEAR_DEPTH | D3D11_CLEAR_FLAG::D3D11_CLEAR_STENCIL, clearDepth, clearStencil);
	}

	void DepthStencilDX11::ClearDepth(float clearDepth)
	{
		auto deviceContext = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDeviceContext();
		deviceContext->ClearDepthStencilView(depthStencilTextureView.Get(), D3D11_CLEAR_FLAG::D3D11_CLEAR_DEPTH, clearDepth, 0u);
	}

	void DepthStencilDX11::ClearStencil(uint clearStencil)
	{
		auto deviceContext = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDeviceContext();
		deviceContext->ClearDepthStencilView(depthStencilTextureView.Get(), D3D11_CLEAR_FLAG::D3D11_CLEAR_STENCIL, 1.0f, clearStencil);
	}

	void DepthStencilDX11::Resize(uint width, uint height)
	{
		Initialize(width, height);
	}

	void DepthStencilDX11::Reset()
	{
		depthStencilTextureView.Reset();
		depthStencilTexture.Reset();
	}

	ID3D11DepthStencilView* DepthStencilDX11::GetView() const noexcept
	{
		return depthStencilTextureView.Get();
	}

	ID3D11DepthStencilView* const* DepthStencilDX11::GetViewAddress() const noexcept
	{
		return depthStencilTextureView.GetAddressOf();
	}

	////////////////////////////////// RenderTargetDX11

	RenderTargetDX11::RenderTargetDX11(uint width, uint height)
	{
		Initialize(width, height);
	}

	void RenderTargetDX11::Initialize(uint width, uint height)
	{
		if (renderTargetTexture || renderTargetView)
		{
			renderTargetTexture.Reset();
			renderTargetView.Reset();
		}
		D3D11_TEXTURE2D_DESC textureDesc = { 0 };
		textureDesc.Width = width;
		textureDesc.Height = height;
		textureDesc.MipLevels = 1u;
		textureDesc.ArraySize = 1u;
		textureDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
		textureDesc.SampleDesc.Count = 1u;
		textureDesc.SampleDesc.Quality = 0u;
		textureDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET;
		textureDesc.CPUAccessFlags = 0u;
		textureDesc.MiscFlags = 0u;

		auto device = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDevice();
		GFX_CHECK_HR(device->CreateTexture2D(&textureDesc, nullptr, renderTargetTexture.GetAddressOf()));
		GFX_CHECK_HR(device->CreateRenderTargetView(renderTargetTexture.Get(), nullptr, renderTargetView.GetAddressOf()));
	}

	void RenderTargetDX11::Bind(DepthStencil* depthStencil)
	{
		auto deviceContext = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDeviceContext();
		deviceContext->OMSetRenderTargets(1u, renderTargetView.GetAddressOf(), depthStencil ? reinterpret_cast<DepthStencilDX11*>(depthStencil)->GetView() : nullptr);
	}

	void RenderTargetDX11::Clear(const float* clearColor)
	{
		auto deviceContext = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDeviceContext();
		deviceContext->ClearRenderTargetView(renderTargetView.Get(), clearColor);
	}

	bool RenderTargetDX11::Resize(uint width, uint height)
	{
		Initialize(width, height);
		return true;
	}

	void RenderTargetDX11::Reset()
	{
		renderTargetView.Reset();
		renderTargetTexture.Reset();
	}

	ID3D11RenderTargetView* RenderTargetDX11::GetView() const noexcept
	{
		return renderTargetView.Get();
	}

	ID3D11RenderTargetView* const* RenderTargetDX11::GetViewAddress() const noexcept
	{
		return renderTargetView.GetAddressOf();
	}

	////////////////////////////////// WindowRenderTargetDX11

	void LimeEngine::WindowRenderTargetDX11::Initialize(ID3D11Texture2D* outTexture)
	{
		auto device = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDevice();
		GFX_CHECK_HR(device->CreateRenderTargetView(outTexture, nullptr, renderTargetView.GetAddressOf()));
	}

	void WindowRenderTargetDX11::Bind(DepthStencil* depthStencil)
	{
		auto deviceContext = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDeviceContext();
		deviceContext->OMSetRenderTargets(1u, renderTargetView.GetAddressOf(), depthStencil ? reinterpret_cast<DepthStencilDX11*>(depthStencil)->GetView() : nullptr);
	}

	void WindowRenderTargetDX11::Clear(const float* clearColor)
	{
		auto deviceContext = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDeviceContext();
		deviceContext->ClearRenderTargetView(renderTargetView.Get(), clearColor);
	}

	bool WindowRenderTargetDX11::Resize(uint width, uint height)
	{
		return false;
	}

	void LimeEngine::WindowRenderTargetDX11::Reset()
	{
		renderTargetView.Reset();
	}
}
